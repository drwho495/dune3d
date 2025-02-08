#include "tool_enter_datum.hpp"
#include "document/document.hpp"
#include "document/entity/entity.hpp"
#include "document/constraint/constraint.hpp"
#include "document/constraint/constraint_point_distance_hv.hpp"
#include "document/constraint/iconstraint_datum.hpp"

#include "editor/editor_interface.hpp"
#include "dialogs/dialogs.hpp"
#include "dialogs/enter_datum_window.hpp"
#include "tool_common_impl.hpp"

namespace dune3d {

static std::optional<UUID> constraint_from_selection(const std::set<SelectableRef> &sel)
{
    if (sel.size() != 1)
        return {};
    auto &sr = *sel.begin();

    if (sr.type != SelectableRef::Type::CONSTRAINT)
        return {};

    return sr.item;
}

ToolBase::CanBegin ToolEnterDatum::can_begin()
{
    auto uu = constraint_from_selection(m_selection);
    if (!uu)
        return false;
    auto &constr = get_doc().get_constraint(*uu);
    auto dat = dynamic_cast<IConstraintDatum *>(&constr);
    if (!dat)
        return false;
    if (dat->is_measurement())
        return false;
    return true;
}

ToolResponse ToolEnterDatum::begin(const ToolArgs &args)
{
    if (m_selection.size() != 1)
        return ToolResponse::end();
    auto &sr = *m_selection.begin();

    if (sr.type != SelectableRef::Type::CONSTRAINT)
        return ToolResponse::end();

    auto &constr = get_doc().get_constraint(sr.item);
    m_constraint = dynamic_cast<IConstraintDatum *>(&constr);


    if (!m_constraint)
        return ToolResponse::end();

    double def = m_constraint->get_datum();

    auto win = m_intf.get_dialogs().show_enter_datum_window("Enter " + m_constraint->get_datum_name(),
                                                            m_constraint->get_datum_unit(), def);


    auto rng = m_constraint->get_datum_range();
    win->set_range(rng.first, rng.second);
    m_intf.set_no_canvas_update(true);
    m_intf.canvas_update_from_tool();


    return ToolResponse();
}

ToolResponse ToolEnterDatum::update(const ToolArgs &args)
{
    if (args.type == ToolEventType::DATA) {
        if (auto data = dynamic_cast<const ToolDataWindow *>(args.data.get())) {
            if (data->event == ToolDataWindow::Event::UPDATE) {
                if (auto d = dynamic_cast<const ToolDataEnterDatumWindow *>(args.data.get())) {
                    m_constraint->set_datum(d->value);
                    // can only edit contraints in current group
                    set_current_group_solve_pending();
                    m_core.solve_current();
                    set_first_update_group_current();
                    m_intf.canvas_update_from_tool();
                }
            }
            else if (data->event == ToolDataWindow::Event::OK) {
                return ToolResponse::commit();
            }
            else if (data->event == ToolDataWindow::Event::CLOSE) {
                return ToolResponse::revert();
            }
        }
    }
    return ToolResponse();
}
} // namespace dune3d
