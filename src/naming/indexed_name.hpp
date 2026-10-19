#pragma once

#include "nlohmann/json_fwd.hpp"
#include <cstdint>
#include <TopAbs_ShapeEnum.hxx>
#include <string>

namespace dune3d {
using json = nlohmann::json;

class IndexedName {
public:
    IndexedName() = default;
    IndexedName(TopAbs_ShapeEnum element_type, uint32_t index) : m_element_type(element_type), m_index(index) { };

    bool operator==(const IndexedName& other) const {
        return (
            m_element_type == other.m_element_type
            && m_index == other.m_index
        );
    };

    TopAbs_ShapeEnum m_element_type;
    uint32_t m_index = 0;

    std::size_t hash() const;

    std::string to_string() const;
private:
    static constexpr std::hash<TopAbs_ShapeEnum> s_element_type_hasher {};
    static constexpr std::hash<uint32_t> s_int_hasher {};
};

} // namespace dune3d


namespace std {
template <> struct hash<dune3d::IndexedName> {
    std::size_t operator()(const dune3d::IndexedName &name) const
    {
        return name.hash();
    }
};
} // namespace std
