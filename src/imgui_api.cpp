#define IMGUI_DEFINE_MATH_OPERATORS
#include "imgui.h"

#include "imgui_animlib.h"

/*typedef struct ImVec2
{
    float x, y;
} ImVec2;*/

bool imgui_animlib_begin(const char *name, bool *show, int wflags)
{
    return ImGui::Begin(name, show, wflags);
}

void imgui_animlib_end()
{
    ImGui::End();
}

void imgui_animlib_text(const char *text)
{
    return ImGui::Text("%s", text);
}

bool imgui_animlib_collapsing_header(const char *text)
{
    return ImGui::CollapsingHeader(text);
}

bool imgui_animlib_button(const char *text)
{
    return ImGui::Button(text);
}

void imgui_animlib_same_line()
{
    ImGui::SameLine();
}

bool imgui_animlib_color_edit4(const char *label, float col[4])
{
    return ImGui::ColorEdit4(label, col);
}

bool imgui_animlib_input_double(const char *label, double *val)
{
    return ImGui::InputDouble(label, val);
}

bool imgui_animlib_input_text(const char *label, char *buf, unsigned int size)
{
    return ImGui::InputText(label, buf, size);
}

ImVec2 imgui_animlib_get_mouse_pos()
{
    return (ImVec2)ImGui::GetMousePos();
}

bool imgui_animlib_begin_drag_drop_target()
{
    return ImGui::BeginDragDropTarget();
}

void imgui_animlib_end_drag_drop_target()
{
    ImGui::EndDragDropTarget();
}

const void* imgui_animlib_accept_drag_drop_payload(const char *name)
{
    return ImGui::AcceptDragDropPayload(name);
}

void imgui_animlib_set_next_window_size(ImVec2 size, int cond_flags)
{
    return ImGui::SetNextWindowSize(size, cond_flags);
}

void imgui_animlib_columns(int count)
{
    return ImGui::Columns(count);
}

void imgui_animlib_separator()
{
    return ImGui::Separator();
}

void imgui_animlib_spacing()
{
    return ImGui::Spacing();
}

void imgui_animlib_push_style_var_float(int idx, float val)
{
    return ImGui::PushStyleVar(idx, val);
}

void imgui_animlib_push_style_var_float2(int idx, ImVec2* val)
{
    return ImGui::PushStyleVar(idx, *val);
}

void imgui_animlib_pop_style_var(int count)
{
    return ImGui::PopStyleVar(count);
}

bool imgui_animlib_begin_menu_bar()
{
    return ImGui::BeginMenuBar();
}

void imgui_animlib_end_menu_bar()
{
    ImGui::EndMenuBar();
}

bool imgui_animlib_begin_menu(const char *label)
{
    return ImGui::BeginMenu(label);
}

void imgui_animlib_end_menu()
{
    ImGui::EndMenu();
}

bool imgui_animlib_menu_item(const char *item)
{
    return ImGui::MenuItem(item);
}

ImVec2 imgui_animlib_get_window_size()
{
    return ImGui::GetWindowSize();
}

void imgui_animlib_push_style_color_u32(int idx, ImU32 col)
{
    ImGui::PushStyleColor(idx, col);
}

void imgui_animlib_push_style_color_float4(int idx, ImVec4 const *col)
{
    ImGui::PushStyleColor(idx, *col);
}

void imgui_animlib_pop_style_color(int count)
{
    ImGui::PopStyleColor(count);
}

bool imgui_animlib_list_box(const char *label, int *current_item, const char* const items[], int items_count, int height_in_items)
{
    return ImGui::ListBox(label, current_item, items, items_count, height_in_items);
}

bool imgui_animlib_input_float(const char *label, float *v)
{
    return ImGui::InputFloat(label, v);
}

bool imgui_animlib_input_float2(const char *label, float v[])
{
    return ImGui::InputFloat2(label, v);
}

bool imgui_animlib_input_float3(const char *label, float v[])
{
    return ImGui::InputFloat3(label, v);
}

bool imgui_animlib_is_mouse_clicked(int button, bool repeat)
{
    return ImGui::IsMouseClicked(button, repeat);
}

bool imgui_animlib_is_mouse_down(int button)
{
    return ImGui::IsMouseDown(button);
}

bool imgui_animlib_begin_combo(const char *label, const char *preview_value, int flags)
{
    return ImGui::BeginCombo(label, preview_value, flags);
}

void imgui_animlib_end_combo()
{
    return ImGui::EndCombo();
}

bool imgui_animlib_selectable1(const char *label, bool *p_selected, int flags, const ImVec2 *size)
{
    ImVec2 size2;
    if (size == nullptr)
    {
        size2 = ImVec2(0.0f, 0.0f);
    }
    else
    {
        size2 = *size;
    }
    return ImGui::Selectable(label, p_selected, flags, *size);
}

bool imgui_animlib_selectable2(const char *label, bool selected, int flags, const ImVec2 *size)
{
    ImVec2 size2;
    if (size == nullptr)
    {
        size2 = ImVec2(0.0f, 0.0f);
    }
    else
    {
        size2 = *size;
    }
    return ImGui::Selectable(label, selected, flags, *size);
}

void imgui_animlib_fg_circle_filled(ImVec2 screen_pos, float radius, ImU32 col)
{
    ImGui::GetForegroundDrawList()->AddCircleFilled(screen_pos, radius, col);
}

void imgui_animlib_fg_text(ImVec2 screen_pos, ImU32 col, const char *text_begin)
{
    ImGui::GetForegroundDrawList()->AddText(screen_pos, col, text_begin);
}

bool imgui_animlib_tree_node(const char* item)
{
    return ImGui::TreeNode(item);
}

void imgui_animlib_tree_pop()
{
    ImGui::TreePop();
}

void imgui_animlib_add_input_character(unsigned int c)
{
    if (ImGui::GetCurrentContext() == nullptr)
    {
        return;
    }
    auto io = &ImGui::GetIO();
    io->AddInputCharacter(c);
}

void imgui_animlib_key_edge(unsigned int key, bool newstate)
{
    if (ImGui::GetCurrentContext() == nullptr)
    {
        return;
    }
    auto io = &ImGui::GetIO();
    io->KeysDown[key] = newstate;
}

