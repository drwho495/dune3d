#pragma once

#include <vector>
#include "history_transformation.hpp"

namespace dune3d {

constexpr uint8_t PERSISTENT_NAME_VERSION = 1;

class SolidModelPersistentName {
public:
    SolidModelPersistentName() = default;
    SolidModelPersistentName(const std::vector<HistoryTransformation>& baseData) : m_data(baseData) { };
    SolidModelPersistentName(const SolidModelPersistentName& otherName) = default;
private:
    uint8_t m_nameVersion = PERSISTENT_NAME_VERSION;
    std::vector<HistoryTransformation> m_data; // 24 byte container
};
} // namespace dune3d