#include "tool_constrain_parallel.hpp"
#include "document/document.hpp"
#include "document/entity/entity.hpp"
#include "document/constraint/constraint_parallel.hpp"
#include "util/selection_util.hpp"
#include "tool_common_constrain_impl.hpp"
#include "core/tool_id.hpp"

namespace dune3d {

static std::optional<std::pair<UUID, UUID>> two_entities_from_selection(const Document &doc,
                                                                        const std::set<SelectableRef> &sel_all)
{
    const auto sel = entities_from_selection(sel_all);

    if (sel.size() != 2)
        return {};
    auto it = sel.begin();
    auto &sr1 = *it++;
    auto &sr2 = *it;

    if (sr1.type != SelectableRef::Type::ENTITY)
        return {};
    if (sr2.type != SelectableRef::Type::ENTITY)
        return {};

    auto &en1 = doc.get_entity(sr1.item);
    auto &en2 = doc.get_entity(sr2.item);
    const auto t1 = en1.get_type();
    const auto t2 = en2.get_type();
    if ((t1 == Entity::Type::LINE_3D && sr1.point == 0 && t2 == Entity::Type::WORKPLANE)
        || (t1 == Entity::Type::WORKPLANE && t2 == Entity::Type::LINE_3D && sr2.point == 0)
        || ((t1 == Entity::Type::LINE_2D || t1 == Entity::Type::LINE_3D)
            && (t2 == Entity::Type::LINE_2D || t2 == Entity::Type::LINE_3D) && (sr1.point == 0) && (sr2.point == 0)))
        return {{en1.m_uuid, en2.m_uuid}};

    return {};
}

bool ToolConstrainParallel::is_force_unset_workplane()
{
    return m_tool_id == ToolID::CONSTRAIN_PARALLEL_3D;
}

bool ToolConstrainParallel::constraint_is_in_workplane()
{
    return get_workplane_uuid() != UUID{};
}

ToolID ToolConstrainParallel::get_force_unset_workplane_tool()
{
    auto wrkpl = get_workplane_uuid();
    if (!wrkpl)
        return ToolID::NONE;

    auto tp = two_entities_from_selection(get_doc(), m_selection);
    if (!tp)
        return ToolID::NONE;

    std::set<EntityAndPoint> enps = {{tp->first, 0}, {tp->second, 0}};

    if (all_entities_in_current_workplane(enps))
        return ToolID::NONE;

    return ToolID::CONSTRAIN_PARALLEL_3D;
}

ToolBase::CanBegin ToolConstrainParallel::can_begin()
{
    const auto &doc = get_doc();
    auto tp = two_entities_from_selection(doc, m_selection);

    if (!tp.has_value())
        return false;

    std::set<EntityAndPoint> enps = {{tp->first, 0}, {tp->second, 0}};

    if (!any_entity_from_current_group(enps))
        return false;


    if (has_constraint_of_type_in_workplane(enps, Constraint::Type::PARALLEL, Constraint::Type::LINES_PERPENDICULAR,
                                            Constraint::Type::LINES_ANGLE))
        return false;

    const auto wrkpl = get_workplane_uuid();
    if (entity_is_constrained_hv(doc, tp->first, wrkpl) && entity_is_constrained_hv(doc, tp->second, wrkpl))
        return false;

    return true;
}

ToolResponse ToolConstrainParallel::begin(const ToolArgs &args)
{
    auto tp = two_entities_from_selection(get_doc(), m_selection);
    if (!tp)
        return ToolResponse::end();

    auto &constraint = add_constraint<ConstraintParallel>();
    constraint.m_entity1 = tp->first;
    constraint.m_entity2 = tp->second;
    constraint.m_wrkpl = get_workplane_uuid();

    return commit();
}

} // namespace dune3d
