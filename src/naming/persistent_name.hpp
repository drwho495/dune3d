#pragma once

#include <vector>
#include "history_transformation_base.hpp"

namespace dune3d {

constexpr uint8_t PERSISTENT_NAME_VERSION = 1;

class PersistentName {
public:
    PersistentName() = default;
    PersistentName(const std::vector<HistoryTransformation>& transformations) : m_transformations(transformations) { };
    PersistentName(const PersistentName& other_name) = default;

    bool operator==(const PersistentName &other) const = default;

    uint8_t m_name_version = PERSISTENT_NAME_VERSION;
    uint32_t duplicateIndex = 0;
    std::vector<HistoryTransformation> m_transformations; // 24 byte container
};
} // namespace dune3d