#include "indexed_name.hpp"
#include "util/util.hpp"

namespace dune3d {

std::size_t IndexedName::hash() const {
    std::size_t returnHash = 0;

    hash_combine(returnHash, s_element_type_hasher(m_element_type));
    hash_combine(returnHash, s_int_hasher(m_index));

    return returnHash;
}

} // namespace dune3d
