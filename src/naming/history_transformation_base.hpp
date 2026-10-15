#pragma once

#include <TopAbs_ShapeEnum.hxx>
#include <vector>

#include "nlohmann/json_fwd.hpp"
#include "util/uuid.hpp"

namespace dune3d {
using json = nlohmann::json;

enum class HistoryTransformationType {
    BASE,
    ENTITY,
    UPGRADE,
    DOWNGRADE,
    SPLIT,
};

class HistoryTransformation {
public:
    HistoryTransformation() = default;
    HistoryTransformation(const HistoryTransformation& other) = default;
    virtual ~HistoryTransformation() = default;

    virtual json serialize() const;

    virtual bool operator==(const HistoryTransformation& other) const {
        return m_element_type == other.m_element_type;
    };

    virtual HistoryTransformationType get_type() const {
        return s_type;
    };

    virtual const UUID* get_owner_group_ID() const {
        return nullptr;
    };

    virtual const UUID* get_iteration_group_ID() const {
        return nullptr;
    };

    TopAbs_ShapeEnum m_element_type;
private:
    static constexpr HistoryTransformationType s_type = HistoryTransformationType::BASE;
};


} // namespace dune3d