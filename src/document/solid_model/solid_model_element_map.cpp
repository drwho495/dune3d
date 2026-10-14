#include "solid_model_element_map.hpp"

namespace dune3d {

void SolidModelElementMap::setPersistentName(const TopoDS_Shape &subElement, const SolidModelPersistentName &name) {
    setPersistentName(m_shapeHasher(subElement), name);
}

void SolidModelElementMap::setPersistentName(const size_t &subElementHash, const SolidModelPersistentName &name) {
    // TODO: handle duplicates
    m_internalData[subElementHash].push_back(name);
}

} // namespace dune3d