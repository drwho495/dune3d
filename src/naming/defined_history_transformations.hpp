#pragma once

#include "persistent_name.hpp"

namespace dune3d {

// A `EntityTransformation` links an element to its source entity ID.
class EntityTransformation : HistoryTransformation {
public:
    json serialize() const override;
    bool operator==(const HistoryTransformation& other) const override;

    /// The entity that created this element.
    UUID m_entity_ID;
    /// The group using this element (e.g. an extrusion).
    UUID m_owner_group_ID;

    HistoryTransformationType get_type() const override {
        return s_type;
    };

    const UUID* get_owner_group_ID() const override {
        return &m_entity_ID;
    };
private:
    static constexpr HistoryTransformationType s_type = HistoryTransformationType::ENTITY;
};

// A `UpgradeTransformation` records when one or more elements is upgraded into geometry of an upper type (edge -> face).
class UpgradeTransformation : HistoryTransformation {
public:
    json serialize() const override;
    bool operator==(const HistoryTransformation& other) const override;

    bool m_has_common_elements = false;
    std::vector<PersistentName> m_source_names;
private:
    static constexpr HistoryTransformationType s_type = HistoryTransformationType::UPGRADE;
};

// A `DowngradeTransformation` records when one or more elements is downgraded into geometry of a lower type (face -> edge).
class DowngradeTransformation : HistoryTransformation {
public:
    json serialize() const override;
    bool operator==(const HistoryTransformation& other) const override;

    std::vector<PersistentName> m_source_names;
private:
    static constexpr HistoryTransformationType s_type = HistoryTransformationType::DOWNGRADE;
};

class SplitTransformation : HistoryTransformation {
public:
    json serialize() const override;
    bool operator==(const HistoryTransformation& other) const override;

    UUID m_iteration_group_ID;
    std::vector<PersistentName> m_connectedNames;

    const UUID* get_iteration_group_ID() const override {
        return &m_iteration_group_ID;
    };
private:
    static constexpr HistoryTransformationType s_type = HistoryTransformationType::SPLIT;
};

} // namespace dune3d