#pragma once

#include <TopAbs_ShapeEnum.hxx>
#include <vector>

#include "nlohmann/json_fwd.hpp"
#include "util/uuid.hpp"

namespace dune3d {
using json = nlohmann::json;

enum class HistoryNodeType {
    BASE,
    ENTITY,
    UPGRADE,
    DOWNGRADE,
    SPLIT,
};

class HistoryNode {
public:
    HistoryNode() = default;
    HistoryNode(const HistoryNode& other) = default;
    virtual ~HistoryNode() = default;

    virtual json serialize() const;

    virtual bool operator==(const HistoryNode& other) const {
        return m_element_type == other.m_element_type && m_duplicate_index == other.m_duplicate_index;
    };

    virtual HistoryNodeType get_type() const {
        return s_type;
    };

    virtual const UUID* get_iteration_group_ID() const {
        return nullptr;
    };

    TopAbs_ShapeEnum m_element_type = TopAbs_SHAPE;
    uint32_t m_duplicate_index = 0;
private:
    static constexpr HistoryNodeType s_type = HistoryNodeType::BASE;
};


} // namespace dune3d