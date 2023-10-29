#define IMGUI_DEFINE_MATH_OPERATORS
#include "imgui.h"
#include "imgui_internal.h"

bool Seekbar(const char* label, float* v, float v_min, float v_max)
{
    ImGuiWindow* window = ImGui::GetCurrentWindow();
    if (window->SkipItems)
    {
        return false;
    }

    ImGuiContext& g = *GImGui;
    const ImGuiStyle& style = g.Style;
    const ImGuiID id = window->GetID(label);
    const ImVec2 label_size = ImGui::CalcTextSize(label, NULL, true);
    ImGui::PushItemWidth(-1);
    const float w = ImGui::CalcItemWidth();

    const ImVec2 seekbar_size = ImVec2(w, label_size.y + style.FramePadding.y * 2.0f);

    const ImRect frame_bb(window->DC.CursorPos, window->DC.CursorPos + seekbar_size);
    const ImRect total_bb(frame_bb.Min, frame_bb.Max + ImVec2(label_size.x > 0.0f ? style.ItemInnerSpacing.x + label_size.x : 0.0f, 0.0f));

    window->DrawList->AddRect(frame_bb.Min, frame_bb.Max, ImGui::GetColorU32(ImGuiCol_FrameBg));

    ImGui::ItemSize(total_bb, style.FramePadding.y);
    if (!ImGui::ItemAdd(total_bb, id, &frame_bb, 0))
    {
        return false;
    }

    const bool hovered = ImGui::ItemHoverable(frame_bb, id, g.LastItemData.InFlags);
    {
        const bool clicked = hovered && ImGui::IsMouseClicked(0, id);
        const bool make_active = (clicked || g.NavActivateId == id);
        if (make_active)
        {
            ImGui::SetActiveID(id, window);
            ImGui::SetFocusID(id, window);
            ImGui::FocusWindow(window);
            g.ActiveIdUsingNavDirMask |= (1 << ImGuiDir_Left) | (1 << ImGuiDir_Right);
        }
    }

    const ImU32 frame_col = ImGui::GetColorU32(g.ActiveId == id ? ImGuiCol_FrameBgActive : hovered ? ImGuiCol_FrameBgHovered : ImGuiCol_FrameBg);
    ImGui::RenderNavHighlight(frame_bb, id);
    //ImGui::RenderFrame(total_bb.Min, total_bb.Max, frame_col, true, style.FrameRounding);

    ImRect bb = frame_bb;
    // slider behaviour

    const float grab_padding = 2.0f;
    const float slider_sz = seekbar_size.x - style.FramePadding.x * 2.f;
    float grab_sz = style.GrabMinSize;
    grab_sz = ImMin(grab_sz, slider_sz);

    const float slider_usable_sz = slider_sz - grab_sz;
    const float slider_usable_pos_min = frame_bb.Min.x + style.FramePadding.x;
    const float slider_usable_pos_max = frame_bb.Max.x - style.FramePadding.x;

    ImGuiSliderFlags flags = 0;

    bool value_changed = false;
    if (g.ActiveId == id)
    {
        bool set_new_value = false;
        float clicked_t = 0.f;
        if (g.ActiveIdSource == ImGuiInputSource_Mouse)
        {
            if (!g.IO.MouseDown[0])
            {
                ImGui::ClearActiveID();
            }
            else
            {
                const float mouse_abs_pos = g.IO.MousePos.x;
                if (g.ActiveIdIsJustActivated)
                {
                    float grab_t = ImSaturate(((*v - v_min) / (v_max - v_min)));
                    const float grab_pos = ImLerp(slider_usable_pos_min, slider_usable_pos_max, grab_t);
                    const bool clicked_around_grab = (mouse_abs_pos >= grab_pos - grab_sz * 0.5f - 1.0f) && (mouse_abs_pos <= grab_pos + grab_sz*0.5f + 1.0f);
                    g.SliderGrabClickOffset = clicked_around_grab ? mouse_abs_pos - grab_pos : 0.f;
                }
                if (slider_usable_sz > 0.0f)
                {
                    clicked_t = ImSaturate((mouse_abs_pos - slider_usable_pos_min) / slider_usable_sz);
                }
                set_new_value = true;
            }
        }

        if (set_new_value)
        {
            if ((g.LastItemData.InFlags & ImGuiItemFlags_ReadOnly) || (flags & ImGuiSliderFlags_ReadOnly))
            {
                set_new_value = false;
            }
        }

        auto format = "%.3f";

        if (set_new_value)
        {
            float v_new = ImGui::ScaleValueFromRatioT<float, float, float>(ImGuiDataType_Float, clicked_t, v_min, v_max, false, 0.0f, 0.0f);

            // Round to user desired precision based on format string
            if (true && !(flags & ImGuiSliderFlags_NoRoundToFormat))
                v_new = ImGui::RoundScalarWithFormatT<float>(format, ImGuiDataType_Float, v_new);

            // Apply result
            if (*v != v_new)
            {
                *v = v_new;
                value_changed = true;
            }
        }

    }

    ImRect out_grab_bb;
    if (slider_sz < 1.0f)
    {
        out_grab_bb = ImRect(bb.Min, bb.Min);
    }
    else
    {
        // Output grab position so it can be displayed by the caller
        float grab_t = ImGui::ScaleRatioFromValueT<float, float, float>(ImGuiDataType_Float, *v, v_min, v_max, false, 0.0f, 0.0f);
        const float grab_pos = ImLerp(slider_usable_pos_min, slider_usable_pos_max, grab_t);
        out_grab_bb = ImRect(grab_pos - grab_sz * 0.5f, bb.Min.y + grab_padding, grab_pos + grab_sz * 0.5f, bb.Max.y - grab_padding);
    }

    float grab_center_x = (out_grab_bb.Min.x + out_grab_bb.Max.x) * 0.5f;
    float grab_center_y = (out_grab_bb.Min.y + out_grab_bb.Max.y) * 0.5f;

    // Render bar
    const float bar_height = 5.0f;
    ImColor played_color = ImColor(1.0f, 0.0f, 0.0f, 0.5f);
    //ImRect bar_bb = ImRect(ImVec2(slider_usable_pos_min, bb.Min.y + grab_padding + (grab_sz - bar_height) * 0.5f), ImVec2(slider_usable_pos_max, bb.Max.y - grab_padding - (grab_sz - bar_height) * 0.5f));
    ImRect bar_played_bb = ImRect(ImVec2(slider_usable_pos_min, bb.Min.y + grab_padding + (grab_sz - bar_height) * 0.5f), ImVec2(grab_center_x, bb.Max.y - grab_padding - (grab_sz - bar_height) * 0.5f));

    ImRect bar_unplayed_bb = ImRect(ImVec2(grab_center_x, bb.Min.y + grab_padding + (grab_sz - bar_height) * 0.5f), ImVec2(slider_usable_pos_max, bb.Max.y - grab_padding - (grab_sz - bar_height) * 0.5f));
    window->DrawList->AddRectFilled(bar_played_bb.Min, bar_played_bb.Max, played_color);
    window->DrawList->AddRectFilled(bar_unplayed_bb.Min, bar_unplayed_bb.Max, ImGui::GetColorU32(ImGuiCol_FrameBg));

    // Render grab circle
    ImU32 grab_col = ImGui::GetColorU32((g.ActiveId == id) ? ImGuiCol_SliderGrabActive : ImGuiCol_SliderGrab);
    //window->DrawList->AddRectFilled(out_grab_bb.Min, out_grab_bb.Max, grab_col, style.GrabRounding);
    if (hovered || g.ActiveId == id)
    {
        window->DrawList->AddCircleFilled(ImVec2(grab_center_x, grab_center_y), grab_sz * 0.5f, grab_col);
    }

    if (value_changed)
        ImGui::MarkItemEdited(id);

    return value_changed;
}
