#include "mapped_shape_occ.hpp"
#include "util/step_exporter.hpp"
#include <iostream>
#include <memory>
#include <vector>

namespace dune3d {

void MappedShapeOCC::set_root_history_node(const std::shared_ptr<HistoryNode> &node) {
    if (m_element_map) {
        m_element_map->set_history_node({m_shape.ShapeType(), 1}, node);
    }
}

void MappedShapeOCC::set_history_node(const IndexedName &element_indexed_name, const std::shared_ptr<HistoryNode> &node) {
    if (m_element_map) {
        m_element_map->set_history_node(element_indexed_name, node);
    }
}

void MappedShapeOCC::set_history_nodes(const IndexedName &element_indexed_name, const std::vector<std::shared_ptr<HistoryNode>> &nodes) {
    if (m_element_map) {
        m_element_map->set_history_nodes(element_indexed_name, nodes);
    }
}

const std::vector<std::shared_ptr<HistoryNode>>& MappedShapeOCC::get_history_nodes(const IndexedName &element_indexed_name) const {
    if (m_element_map) {
        return m_element_map->get_history_nodes(element_indexed_name);
    }
    return EMPTY_NODE_LIST;
}

const std::vector<TopoDS_Shape>& MappedShapeOCC::get_elements(TopAbs_ShapeEnum element_type) const {
    auto subElementIterator = m_sub_element_table.find(element_type);

    if (subElementIterator != m_sub_element_table.end()) {
        return subElementIterator->second;
    } else {
        std::vector<TopoDS_Shape> elements;

        NCollection_IndexedMap<TopoDS_Shape, TopTools_ShapeMapHasher> subElementOccMap;
        TopExp::MapShapes(m_shape, element_type, subElementOccMap);

        for (const TopoDS_Shape& element : subElementOccMap) {
            elements.push_back(element);
        }

        auto emplacedSubElementIterator = m_sub_element_table.try_emplace(element_type, elements);

        return emplacedSubElementIterator.first->second;
    }
}

} // namespace dune3d
