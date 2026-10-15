#pragma once

#include "mapped_shape_occ.hpp"
#include <vector>

namespace dune3d {
namespace geometry_operations_occ {

MappedShapeOCC fuse(const std::vector<MappedShapeOCC> &tools);

MappedShapeOCC fuse(const MappedShapeOCC &base, const MappedShapeOCC &tool) {
    std::vector<MappedShapeOCC> tools;

    tools.push_back(base);
};
    
} // namespace geometry_operations_occ
} // namespace dune3d