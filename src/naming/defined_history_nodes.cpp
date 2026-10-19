#include "defined_history_nodes.hpp"
#include "nlohmann/json.hpp"

namespace dune3d {

json EntityHistoryNode::serialize() const {
    auto serializedNode = HistoryNode::serialize();
    
    serializedNode["entityID"] = m_entity_ID;

    return serializedNode;
}

bool EntityHistoryNode::operator==(const HistoryNode& other) const {
    if (other.get_type() == HistoryNodeType::ENTITY) {
        const EntityHistoryNode& otherCasted = static_cast<const EntityHistoryNode&>(other);
        
        return (
            HistoryNode::operator==(other)
            && otherCasted.m_entity_ID == m_entity_ID
        );
    }

    return false;
}

} // namespace dune3d