#pragma once

#include "mapped_shape_occ.hpp"
#include <vector>

namespace dune3d {
namespace geometry_operations_occ {

MappedShapeOCC fuse(const std::vector<MappedShapeOCC> &tools);

MappedShapeOCC make_wire(const std::vector<MappedShapeOCC> &edges);

void map_sub_element(MappedShapeOCC &shape, const std::vector<MappedShapeOCC> &source_shapes);
void map_sub_element(MappedShapeOCC &shape, const MappedShapeOCC &source_shape);
    
} // namespace geometry_operations_occ
} // namespace dune3d