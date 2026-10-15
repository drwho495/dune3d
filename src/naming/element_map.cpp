#include "element_map.hpp"

namespace dune3d {

void ElementMap::setPersistentName(const TopoDS_Shape &sub_element, const PersistentName &name) {
    // setPersistentName(m_shape_hasher(subElement), name);
}

void ElementMap::setPersistentName(const IndexedName &sub_element_indexed_name, const PersistentName &name) {
    // TODO: handle duplicates
    m_internal_data[sub_element_indexed_name].push_back(name);
}

} // namespace dune3d