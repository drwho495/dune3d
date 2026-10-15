#pragma once

#include <TopoDS.hxx>
#include <memory>
#include "element_map.hpp"
#include "util/step_exporter.hpp"

namespace dune3d {

class MappedShapeOCC {
public:
    MappedShapeOCC() = default;
    MappedShapeOCC(const MappedShapeOCC &other) = default;
    MappedShapeOCC(const TopoDS_Shape& shape)
        : m_shape(shape) { };

    void set_shape(const TopoDS_Shape &new_shape) {
        m_shape = new_shape;
    };

    void set_shape(const TopoDS_Shape &new_shape, std::shared_ptr<ElementMap> new_element_map) {
        set_shape(new_shape);

        m_element_map = new_element_map;
    };

    bool operator==(const MappedShapeOCC &other) const {
        return (
            m_shape.IsSame(other.m_shape)
            && (m_element_map == other.m_element_map || *m_element_map == *other.m_element_map)
        );
    };

    TopoDS_Shape m_shape;
    std::shared_ptr<ElementMap> m_element_map;
};

} // namespace dune3d
