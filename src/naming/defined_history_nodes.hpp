#pragma once

#include "history_node_base.hpp"
#include "util/uuid.hpp"

namespace dune3d {

// A `EntityHistoryNode` links an element to its source entity ID.
class EntityHistoryNode : public HistoryNode {
public:
    EntityHistoryNode(UUID entity_ID)
        : m_entity_ID(entity_ID) { };

    json serialize() const override;
    bool operator==(const HistoryNode& other) const override;

    /// The entity that created this element.
    UUID m_entity_ID;

    HistoryNodeType get_type() const override {
        return s_type;
    };
private:
    static constexpr HistoryNodeType s_type = HistoryNodeType::ENTITY;
};

// A `UpgradeHistoryNode` records when one or more elements is upgraded into geometry of an upper type (edge -> face).
class UpgradeHistoryNode : public HistoryNode {
public:
    json serialize() const override;
    bool operator==(const HistoryNode& other) const override;

    bool m_has_common_elements = false;
    std::vector<std::shared_ptr<HistoryNode>> m_source_nodes;
private:
    static constexpr HistoryNodeType s_type = HistoryNodeType::UPGRADE;
};

// A `DowngradeHistoryNode` records when one or more elements is downgraded into geometry of a lower type (face -> edge).
class DowngradeHistoryNode : public HistoryNode {
public:
    json serialize() const override;
    bool operator==(const HistoryNode& other) const override;

    std::vector<std::shared_ptr<HistoryNode>> m_source_nodes;
private:
    static constexpr HistoryNodeType s_type = HistoryNodeType::DOWNGRADE;
};

class SplitHistoryNode : public HistoryNode {
public:
    json serialize() const override;
    bool operator==(const HistoryNode& other) const override;

    UUID m_iteration_group_ID;
    std::vector<std::shared_ptr<HistoryNode>> m_connected_nodes;

    const UUID* get_iteration_group_ID() const override {
        return &m_iteration_group_ID;
    };
private:
    static constexpr HistoryNodeType s_type = HistoryNodeType::SPLIT;
};

} // namespace dune3d