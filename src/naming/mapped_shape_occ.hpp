#pragma once

#include <TopoDS.hxx>
#include <memory>
#include <unordered_map>
#include <vector>
#include "element_map.hpp"
#include "naming/history_node_base.hpp"
#include "util/step_exporter.hpp"
#include <TopAbs_ShapeEnum.hxx>

namespace dune3d {

class MappedShapeOCC {
public:
    MappedShapeOCC()
    {
        m_element_map = std::make_shared<ElementMap>();
    };
    MappedShapeOCC(const MappedShapeOCC &other) = default;
    MappedShapeOCC(const TopoDS_Shape& shape)
        : m_shape(shape)
    {
        m_element_map = std::make_shared<ElementMap>();
    };
    MappedShapeOCC(const TopoDS_Shape& shape, const std::shared_ptr<HistoryNode>& node)
        : m_shape(shape)
    {
        m_element_map = std::make_shared<ElementMap>();
        
        set_root_history_node(node);
    };

    MappedShapeOCC(const TopoDS_Shape& shape, const std::shared_ptr<ElementMap>& element_map)
        : m_shape(shape), m_element_map(element_map) {};

    void set(const TopoDS_Shape &new_shape) {
        if (new_shape.IsSame(m_shape)) {
            return;
        }

        m_shape = new_shape;
        m_sub_element_table.clear();
    };

    void set(const TopoDS_Shape &new_shape, std::shared_ptr<ElementMap> new_element_map) {
        set(new_shape);

        m_element_map = new_element_map;
    };

    void set_root_history_node(const std::shared_ptr<HistoryNode> &node);
    void set_history_node(const IndexedName &element_indexed_name, const std::shared_ptr<HistoryNode> &node);
    void set_history_nodes(const IndexedName &element_indexed_name, const std::vector<std::shared_ptr<HistoryNode>> &nodes);

    const std::vector<std::shared_ptr<HistoryNode>>& get_history_nodes(const IndexedName &element_indexed_name) const;

    const std::vector<TopoDS_Shape>& get_elements(TopAbs_ShapeEnum element_type) const;

    bool operator==(const MappedShapeOCC &other) const {
        return (
            m_shape.IsSame(other.m_shape)
            && (m_element_map == other.m_element_map || *m_element_map == *other.m_element_map)
        );
    };

    TopoDS_Shape m_shape;
    std::shared_ptr<ElementMap> m_element_map;
private:
    mutable std::unordered_map<TopAbs_ShapeEnum, std::vector<TopoDS_Shape>> m_sub_element_table;
};

} // namespace dune3d
