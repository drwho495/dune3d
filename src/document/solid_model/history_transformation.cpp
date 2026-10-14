#pragma once

#include "history_transformation.hpp"
#include "nlohmann/json.hpp"

namespace dune3d {

json EntityTransformation::serialize() const {
    auto serializedTransformation = json{
        {"type", "document"}
    };
    
    serializedTransformation[""]

    return j;
}

bool EntityTransformation::isEqual(const HistoryTransformation& other, bool checkDuplicateIndex) const {
    bool check = false;

    if (auto otherCast = dynamic_cast<const EntityTransformation*>(&other)) {
        check = otherCast->entityID == entityID && ownerGroup;
    }

    return (
        HistoryTransformation::isEqual(other, checkDuplicateIndex)
        && check
    );
}

} // namespace dune3d