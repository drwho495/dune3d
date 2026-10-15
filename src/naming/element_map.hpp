#pragma once

#include <cstddef>
#include <functional>
#include <unordered_map>
#include "indexed_name.hpp"
#include "persistent_name.hpp"
#include "util/step_exporter.hpp"
#include <TopExp.hxx>
#include <vector>

namespace dune3d {

class ElementMap {
public:
    ElementMap() = default;
    ElementMap(const ElementMap &other_map) = default;
    ElementMap(const std::unordered_map<IndexedName, std::vector<PersistentName>>& data)
        : m_internal_data(data) { };
    
    void setPersistentName(const TopoDS_Shape &sub_element, const PersistentName &name);
    void setPersistentName(const IndexedName &sub_element_indexed_name, const PersistentName &name);

    bool operator==(const ElementMap &other) const = default;
private:
    // sub-element hash -> persistent name
    std::unordered_map<IndexedName, std::vector<PersistentName>> m_internal_data;
};

} // namespace dune3d
