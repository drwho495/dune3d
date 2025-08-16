#include "tool_constrain_distance.hpp"
#include "document/document.hpp"
#include "document/constraint/constraint_point_distance.hpp"
#include "document/constraint/constraint_point_distance_hv.hpp"
#include "document/entity/ientity_in_workplane.hpp"
#include "util/selection_util.hpp"
#include "util/template_util.hpp"
#include "core/tool_id.hpp"
#include "tool_common_constrain_impl.hpp"

namespace dune3d {

ToolBase::CanBegin ToolConstrainDistance::can_begin()
{
    if (any_of(m_tool_id, ToolID::CONSTRAIN_DISTANCE_HORIZONTAL, ToolID::CONSTRAIN_DISTANCE_VERTICAL,
               ToolID::MEASURE_DISTANCE_HORIZONTAL, ToolID::MEASURE_DISTANCE_VERTICAL)
        && !get_workplane_uuid())
        return false;

    auto tp = two_points_from_selection(get_doc(), m_selection);
    if (!tp)
        return false;

    if (any_of(m_tool_id, ToolID::MEASURE_DISTANCE, ToolID::MEASURE_DISTANCE_HORIZONTAL,
               ToolID::MEASURE_DISTANCE_VERTICAL))
        return true;

    if (!any_entity_from_current_group(tp->get_enps_as_tuple()))
        return false;

    switch (m_tool_id) {
    case ToolID::CONSTRAIN_DISTANCE_HORIZONTAL:
        return !has_constraint_of_type_in_workplane(tp->get_enps(), Constraint::Type::POINT_DISTANCE_HORIZONTAL,
                                                    Constraint::Type::VERTICAL, Constraint::Type::SYMMETRIC_VERTICAL);

    case ToolID::CONSTRAIN_DISTANCE_VERTICAL:
        return !has_constraint_of_type_in_workplane(tp->get_enps(), Constraint::Type::POINT_DISTANCE_VERTICAL,
                                                    Constraint::Type::HORIZONTAL,
                                                    Constraint::Type::SYMMETRIC_HORIZONTAL);

    case ToolID::CONSTRAIN_DISTANCE:
    case ToolID::CONSTRAIN_DISTANCE_3D:
        return !has_constraint_of_type_in_workplane(tp->get_enps(), Constraint::Type::POINT_DISTANCE,
                                                    Constraint::Type::HORIZONTAL, Constraint::Type::VERTICAL,
                                                    Constraint::Type::SYMMETRIC_HORIZONTAL,
                                                    Constraint::Type::SYMMETRIC_VERTICAL);

    default:
        return false;
    }
}

bool ToolConstrainDistance::can_preview_constrain()
{
    return any_of(m_tool_id, ToolID::CONSTRAIN_DISTANCE, ToolID::CONSTRAIN_DISTANCE_3D,
                  ToolID::CONSTRAIN_DISTANCE_HORIZONTAL, ToolID::CONSTRAIN_DISTANCE_VERTICAL);
}

bool ToolConstrainDistance::is_force_unset_workplane()
{
    return m_tool_id == ToolID::CONSTRAIN_DISTANCE_3D;
}

bool ToolConstrainDistance::constraint_is_in_workplane()
{
    return get_workplane_uuid() != UUID{};
}

ToolID ToolConstrainDistance::get_force_unset_workplane_tool()
{
    if (m_tool_id != ToolID::CONSTRAIN_DISTANCE)
        return ToolID::NONE;

    auto wrkpl = get_workplane_uuid();
    if (!wrkpl)
        return ToolID::NONE;

    auto tp = two_points_from_selection(get_doc(), m_selection);
    if (!tp)
        return ToolID::NONE;

    if (all_entities_in_current_workplane(tp->get_enps()))
        return ToolID::NONE;

    return ToolID::CONSTRAIN_DISTANCE_3D;
}


ToolResponse ToolConstrainDistance::begin(const ToolArgs &args)
{
    auto tp = two_points_from_selection(get_doc(), m_selection);

    if (!tp)
        return ToolResponse::end();

    ConstraintPointDistanceBase *constraint = nullptr;
    switch (m_tool_id) {
    case ToolID::CONSTRAIN_DISTANCE_HORIZONTAL:
    case ToolID::MEASURE_DISTANCE_HORIZONTAL:
        constraint = &just_add_constraint<ConstraintPointDistanceHorizontal>();
        break;

    case ToolID::CONSTRAIN_DISTANCE_VERTICAL:
    case ToolID::MEASURE_DISTANCE_VERTICAL:
        constraint = &just_add_constraint<ConstraintPointDistanceVertical>();
        break;

    default:
        constraint = &just_add_constraint<ConstraintPointDistance>();
    }

    if (any_of(m_tool_id, ToolID::MEASURE_DISTANCE, ToolID::MEASURE_DISTANCE_HORIZONTAL,
               ToolID::MEASURE_DISTANCE_VERTICAL))
        constraint->m_measurement = true;
    else
        set_current_group_solve_pending();


    constraint->m_entity1 = tp->point1;
    constraint->m_entity2 = tp->point2;
    constraint->m_wrkpl = get_workplane_uuid();
    auto dist = constraint->measure_distance(get_doc());
    if (dist < 0)
        constraint->flip();
    constraint->m_distance = std::abs(dist);

    return prepare_interactive(*constraint);
}
} // namespace dune3d
