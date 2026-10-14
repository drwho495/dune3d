#pragma once

#include "nlohmann/json_fwd.hpp"
#include "util/uuid.hpp"
#include <cstdint>

namespace dune3d {
using json = nlohmann::json;

class HistoryTransformation {
public:
    HistoryTransformation() = default;
    HistoryTransformation(const HistoryTransformation& otherTransformation) = default;

    virtual json serialize() const;

    bool operator==(const HistoryTransformation& other) const {
        return isEqual(other);
    };

    virtual bool isEqual(const HistoryTransformation& other, bool checkDuplicateIndex = true) const {
        return !checkDuplicateIndex || other.duplicateIndex == duplicateIndex;
    };

    uint32_t duplicateIndex = 0;
};

/// A `HistoryTransformation` that links an OpenCASCADE element to its source SolveSpace entity ID.
// 36 bytes (?)
class EntityTransformation : HistoryTransformation {
public:
    json serialize() const override;
    bool isEqual(const HistoryTransformation& other, bool checkDuplicateIndex) const override;

    /// The entity that created this element.
    UUID entityID;
    /// The group using this element (e.g. an extrusion).
    UUID ownerGroup;
};

} // namespace dune3d