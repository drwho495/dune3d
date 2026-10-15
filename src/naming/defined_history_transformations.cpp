#include "defined_history_transformations.hpp"
#include "nlohmann/json.hpp"

namespace dune3d {

json EntityTransformation::serialize() const {
    auto serializedTransformation = HistoryTransformation::serialize();
    
    serializedTransformation["entityID"] = m_entity_ID;
    serializedTransformation["ownerGroup"] = m_owner_group_ID;

    return serializedTransformation;
}

bool EntityTransformation::operator==(const HistoryTransformation& other) const {
    if (other.get_type() == HistoryTransformationType::ENTITY) {
        const EntityTransformation& otherCasted = static_cast<const EntityTransformation&>(other);
        
        return (
            HistoryTransformation::operator==(other)
            && otherCasted.m_entity_ID == m_entity_ID
            && otherCasted.m_owner_group_ID == m_owner_group_ID
        );
    }

    return false;
}

} // namespace dune3d