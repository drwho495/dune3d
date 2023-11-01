#pragma once
#include "editor_interface.hpp"
#include "core/core.hpp"
#include <gtkmm.h>
#include "action/action.hpp"
#include "preferences/preferences.hpp"
#include "document_view.hpp"
#include "dialogs/dialogs.hpp"
#include "util/action_label.hpp"
#include "document/group/group.hpp"
#include "workspace_browser.hpp"


namespace dune3d {

class Dune3DApplication;
class Canvas;
class Preferences;
enum class ToolID;
class ActionLabelInfo;
class ToolPopover;
class ConstraintsBox;
class GroupEditor;
class SelectionEditor;

class Dune3DAppWindow;

class Editor : private EditorInterface {
public:
    Editor(Dune3DAppWindow &win, Preferences &prefs);

    void init();


    void tool_bar_set_actions(const std::vector<ActionLabelInfo> &labels) override;
    void tool_bar_set_tool_tip(const std::string &s) override;
    void tool_bar_flash(const std::string &s) override;
    void tool_bar_flash_replace(const std::string &s) override;
    glm::dvec3 get_cursor_pos() const override;
    glm::vec3 get_cam_normal() const override;
    glm::dvec3 get_cursor_pos_for_plane(glm::dvec3 origin, glm::dvec3 normal) const override;
    void tool_update_data(std::unique_ptr<ToolData> data) override;
    void enable_hover_selection() override;
    std::optional<SelectableRef> get_hover_selection() const override;
    void set_no_canvas_update(bool v) override
    {
        m_no_canvas_update = v;
    }
    void canvas_update_from_tool() override;

    void set_solid_model_edge_select_mode(bool v) override
    {
        m_solid_model_edge_select_mode = v;
    }

    void open_file(const std::filesystem::path &path);

private:
    void init_workspace_browser();
    void init_properties_notebook();
    void init_header_bar();
    void init_actions();
    void init_tool_popover();
    void init_canvas();

    void on_workspace_browser_group_selected(const UUID &uu_doc, const UUID &uu_group);
    void on_workspace_browser_add_group(Group::Type group_type);
    void on_workspace_browser_delete_current_group();
    void on_workspace_browser_move_group(WorkspaceBrowser::MoveGroup op);
    void on_workspace_browser_group_checked(const UUID &uu_doc, const UUID &uu_group, bool checked);
    void on_workspace_browser_body_checked(const UUID &uu_doc, const UUID &uu_group, bool checked);
    void on_workspace_browser_body_solid_model_checked(const UUID &uu_doc, const UUID &uu_group, bool checked);

    void on_export_solid_model(const ActionConnection &conn);
    void on_open_document(const ActionConnection &conn);
    void on_save_as(const ActionConnection &conn);


    Canvas &get_canvas();
    const Canvas &get_canvas() const;

    Gtk::PopoverMenu *m_context_menu = nullptr;
    double m_rmb_last_x = NAN;
    double m_rmb_last_y = NAN;
    std::set<SelectableRef> m_context_menu_selection;
    void open_context_menu();

    void canvas_update();
    void canvas_update_keep_selection();

    void tool_begin(ToolID id);
    void tool_process(ToolResponse &resp);
    void tool_process_one();
    void handle_cursor_move();
    double m_last_x = NAN;
    double m_last_y = NAN;
    void handle_click(unsigned int button, unsigned int n);


    void apply_preferences();


    Gtk::Button *create_action_button(ActionToolID action);
    void attach_action_button(Gtk::Button &button, ActionToolID action);

    std::map<ActionToolID, ActionConnection> m_action_connections;

    ActionConnection &connect_action(ToolID tool_id);
    ActionConnection &connect_action(ActionToolID id, std::function<void(const ActionConnection &)> cb);
    ActionConnection &connect_action_with_source(ActionToolID id,
                                                 std::function<void(const ActionConnection &, ActionSource)> cb);

    KeySequence m_keys_current;
    KeyMatchResult keys_match(const KeySequence &keys) const;
    bool handle_action_key(Glib::RefPtr<Gtk::EventControllerKey> controller, unsigned int keyval,
                           Gdk::ModifierType state);
    void handle_tool_action(const ActionConnection &conn);

    bool trigger_action(ActionToolID action, ActionSource source = ActionSource::UNKNOWN);
    bool get_action_sensitive(ActionID action) const;

    void update_action_sensitivity();

    std::map<ActionID, bool> m_action_sensitivity;

    void tool_bar_append_action(InToolActionID action1, InToolActionID action2, const std::string &s);
    void tool_bar_clear_actions();
    std::vector<ActionLabelInfo> m_in_tool_action_label_infos;

    sigc::signal<void()> m_signal_action_sensitive;
    Preferences &m_preferences;
    InToolKeySequencesPreferences m_in_tool_key_sequeces_preferences;


    bool m_no_canvas_update = false;
    bool m_solid_model_edge_select_mode = false;

    ToolPopover *m_tool_popover = nullptr;

    WorkspaceBrowser *m_workspace_browser = nullptr;

    void update_workplane_label();
    void update_selection_mode_label();

    Gtk::Notebook *m_properties_notebook = nullptr;
    ConstraintsBox *m_constraints_box = nullptr;
    Gtk::Box *m_group_editor_box = nullptr;
    GroupEditor *m_group_editor = nullptr;
    void update_group_editor();

    SelectionEditor *m_selection_editor = nullptr;
    void update_selection_editor();

    Dialogs m_dialogs;
    Dialogs &get_dialogs() override
    {
        return m_dialogs;
    }

    DocumentView m_document_view;

    void handle_tool_change();

    void reset_key_hint_label();

    void show_save_dialog(std::function<void()> save_cb, std::function<void()> no_save_cb);
    std::function<void()> m_after_save_cb;
    void close_document(const UUID &uu, std::function<void()> save_cb, std::function<void()> no_save_cb);

    std::optional<ActionToolID> get_doubleclick_action(const SelectableRef &sr);
    ToolID get_tool_for_drag_move(bool ctrl, const std::set<SelectableRef> &sel);
    ToolID m_drag_tool;
    std::set<SelectableRef> m_selection_for_drag;
    glm::dvec2 m_cursor_pos_win_drag_begin;

    void update_version_info();

    Dune3DAppWindow &m_win;

    Core m_core;
};
} // namespace dune3d
