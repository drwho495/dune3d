#include "indexed_name.hpp"
#include "util/util.hpp"
#include "nlohmann/json.hpp"
#include <string>

namespace dune3d {

std::size_t IndexedName::hash() const {
    std::size_t returnHash = 0;

    hash_combine(returnHash, s_element_type_hasher(m_element_type));
    hash_combine(returnHash, s_int_hasher(m_index));

    return returnHash;
}

std::string IndexedName::to_string() const {
    auto returnString = std::to_string(static_cast<unsigned int>(m_element_type));

    returnString += "_";
    returnString += std::to_string(m_index);

    return returnString;
}

} // namespace dune3d
