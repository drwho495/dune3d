#include "tool_constrain_point_line_distance.hpp"
#include "document/constraint/constraint_point_line_distance.hpp"
#include "util/selection_util.hpp"
#include "util/template_util.hpp"
#include "tool_common_constrain_impl.hpp"
#include "core/tool_id.hpp"

namespace dune3d {

ToolBase::CanBegin ToolConstrainPointLineDistance::can_begin()
{
    auto lp = line_and_point_from_selection(get_doc(), m_selection, LineAndPoint::AllowSameEntity::NO);
    if (!lp)
        return false;

    if (m_tool_id == ToolID::MEASURE_POINT_LINE_DISTANCE)
        return true;

    if (!any_entity_from_current_group(lp->get_enps_as_tuple()))
        return false;

    return !has_constraint_of_type_in_workplane(lp->get_enps(), Constraint::Type::POINT_LINE_DISTANCE,
                                                Constraint::Type::POINT_ON_LINE, Constraint::Type::MIDPOINT);
}

bool ToolConstrainPointLineDistance::can_preview_constrain()
{
    return any_of(m_tool_id, ToolID::CONSTRAIN_POINT_LINE_DISTANCE, ToolID::CONSTRAIN_POINT_LINE_DISTANCE_3D);
}

bool ToolConstrainPointLineDistance::is_force_unset_workplane()
{
    return m_tool_id == ToolID::CONSTRAIN_POINT_LINE_DISTANCE_3D;
}

bool ToolConstrainPointLineDistance::constraint_is_in_workplane()
{
    return get_workplane_uuid() != UUID{};
}

ToolID ToolConstrainPointLineDistance::get_force_unset_workplane_tool()
{
    auto wrkpl = get_workplane_uuid();
    if (!wrkpl)
        return ToolID::NONE;

    auto lp = line_and_point_from_selection(get_doc(), m_selection, LineAndPoint::AllowSameEntity::NO);
    if (!lp)
        return ToolID::NONE;
    ;
    if (all_entities_in_current_workplane(lp->get_enps()))
        return ToolID::NONE;

    return ToolID::CONSTRAIN_POINT_LINE_DISTANCE_3D;
}

ToolResponse ToolConstrainPointLineDistance::begin(const ToolArgs &args)
{
    auto lp = line_and_point_from_selection(get_doc(), m_selection, LineAndPoint::AllowSameEntity::NO);

    if (!lp)
        return ToolResponse::end();

    auto &constraint = add_constraint<ConstraintPointLineDistance>();
    constraint.m_line = lp->line;
    constraint.m_point = lp->point;
    constraint.m_wrkpl = get_workplane_uuid();
    constraint.m_modify_to_satisfy = true;
    constraint.m_measurement = m_tool_id == ToolID::MEASURE_POINT_LINE_DISTANCE;

    if (!m_is_preview)
        m_core.solve_current();

    return prepare_interactive(constraint);
}

} // namespace dune3d
