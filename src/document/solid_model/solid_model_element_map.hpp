#pragma once

#include <cstddef>
#include <functional>
#include <unordered_map>
#include "solid_model_persistent_name.hpp"
#include "util/step_exporter.hpp"
#include <TopExp.hxx>
#include <vector>

namespace dune3d {

class SolidModelElementMap {
public:
    SolidModelElementMap() = default;
    SolidModelElementMap(const SolidModelElementMap &otherMap) = default;
    SolidModelElementMap(const std::unordered_map<size_t, std::vector<SolidModelPersistentName>>& data)
        : m_internalData(data) { };
    
    void setPersistentName(const TopoDS_Shape &subElement, const SolidModelPersistentName &name);
    void setPersistentName(const size_t &subElementHash, const SolidModelPersistentName &name);
private:
    // sub-element hash -> persistent name
    std::unordered_map<size_t, std::vector<SolidModelPersistentName>> m_internalData;
    TopTools_ShapeMapHasher m_shapeHasher;
};

} // namespace dune3d