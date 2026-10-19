#include "geometry_operations_occ.hpp"
#include <BRepBuilderAPI_MakeWire.hxx>
#include "indexed_name.hpp"
#include "mapped_shape_occ.hpp"
#include "nlohmann/json.hpp"
#include "util/step_exporter.hpp"
#include <functional>
#include <iostream>
#include <memory>
#include <string>
#include <vector>
#include <BRep_Tool.hxx>
#include <TopoDS_Wire.hxx>

namespace dune3d {
namespace geometry_operations_occ {

MappedShapeOCC fuse(const std::vector<MappedShapeOCC> &tools) {
    return {};
}

MappedShapeOCC make_wire(const std::vector<MappedShapeOCC> &edges) {
    std::vector<const MappedShapeOCC*> filteredEdges;
    std::vector<const MappedShapeOCC*> sortedEdges;
    std::vector<MappedShapeOCC> fixedInputEdges;
    BRepBuilderAPI_MakeWire wireBuilder;

    filteredEdges.reserve(edges.size());

    for (const MappedShapeOCC &edge : edges) {
        if (edge.m_shape.ShapeType() == TopAbs_EDGE) {
            filteredEdges.push_back(&edge);
        }
    }

    const MappedShapeOCC* currentEdge = filteredEdges.front();
    const std::vector<TopoDS_Shape>* currentEdgeVertices = &currentEdge->get_elements(TopAbs_VERTEX);
    bool foundConnection = false;

    fixedInputEdges.reserve(filteredEdges.size());
    sortedEdges.reserve(filteredEdges.size());
    sortedEdges.push_back(currentEdge);

    // sort edges by connected vertices, this is necessary to preserve element naming.
    while (sortedEdges.size() != filteredEdges.size()) {
        foundConnection = false;

        for (const MappedShapeOCC* loopEdge : filteredEdges) {
            if (std::find(sortedEdges.begin(), sortedEdges.end(), loopEdge) != sortedEdges.end()) {
                continue;
            }

            const std::vector<TopoDS_Shape> &loopEdgeVertices = loopEdge->get_elements(TopAbs_VERTEX);

            for (const TopoDS_Shape &currentEdgeVertex : *currentEdgeVertices) {
                gp_Pnt currentEdgeVertexPoint = BRep_Tool::Pnt(TopoDS::Vertex(currentEdgeVertex));

                for (const TopoDS_Shape &loopEdgeVertex : loopEdgeVertices) {
                    gp_Pnt loopEdgeVertexPoint = BRep_Tool::Pnt(TopoDS::Vertex(loopEdgeVertex));

                    if (currentEdgeVertexPoint.Distance(loopEdgeVertexPoint) <= Precision::Confusion()) {
                        sortedEdges.push_back(loopEdge);
                        
                        currentEdge = loopEdge;
                        currentEdgeVertices = &loopEdgeVertices;
                        foundConnection = true;

                        break;
                    }
                }

                if (foundConnection) {
                    break;
                }
            }
            if (foundConnection) {
                break;
            }
        }
    }

    for (const MappedShapeOCC *sortedEdge : sortedEdges) {
        wireBuilder.Add(TopoDS::Edge(sortedEdge->m_shape));

        // when `BRepBuilderAPI_MakeWire` finds edges with shared vertices, it connects them together.
        // this process modifies the geometry of the `sortedEdge`. we use `BRepBuilderAPI_MakeWire::Edge()`
        // to retrieve the newly created element with this modified geometry. we then
        // emplace that element onto a vector for mapping.
        fixedInputEdges.emplace_back(wireBuilder.Edge(), edge->m_element_map);
    }

    MappedShapeOCC returnShape {wireBuilder.Wire()};
    map_sub_element(returnShape, fixedInputEdges);

    return returnShape;
}

void map_sub_element(MappedShapeOCC &shape, const std::vector<MappedShapeOCC> &source_shapes) {
    for (const MappedShapeOCC &source_shape : source_shapes) {
        map_sub_element(shape, source_shape);
    }
}

void map_sub_element(MappedShapeOCC &shape, const MappedShapeOCC &source_shape) {
    if (!shape.m_element_map) {
        shape.m_element_map = std::make_shared<ElementMap>();
    }

    unsigned int newElementIdx = 0;
    unsigned int sourceElementIdx = 0;

    IndexedName newIdxName;

    for (const TopAbs_ShapeEnum& type : {TopAbs_EDGE, TopAbs_VERTEX, TopAbs_FACE}) {
        const std::vector<TopoDS_Shape>& newElements = shape.get_elements(type);
        const std::vector<TopoDS_Shape>& sourceElements = source_shape.get_elements(type);

        newIdxName.m_element_type = type;

        for (const TopoDS_Shape& newElement : newElements) {
            newIdxName.m_index = ++newElementIdx;

            for (const TopoDS_Shape& sourceElement : sourceElements) {
                sourceElementIdx++;

                if (newElement.IsSame(sourceElement)) {
                    const std::vector<std::shared_ptr<HistoryNode>> &names = source_shape.get_history_nodes({type, sourceElementIdx});

                    if (names.size()) {
                        shape.set_history_nodes(
                            newIdxName,
                            names
                        );
                    }
                }
            }

            sourceElementIdx = 0;
        }

        newElementIdx = 0;
    }
}

} // namespace geometry_operations_occ
} // namespace dune3d