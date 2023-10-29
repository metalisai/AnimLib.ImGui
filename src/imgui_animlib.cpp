#define IMGUI_DEFINE_MATH_OPERATORS
#include "imgui.h"

#include <cstdio>
#include <cstdint>
#include "imgui_animlib.h"
#include <string>

#define ICON_FA_HEART "\uf004"
#define ICON_FA_PLAY "\uf04b"
#define ICON_FA_PAUSE "\uf04c"

void test_window();

struct ImGuiAnimlibState
{
    ImGuiContext* ctx;
    imgui_animlib_draw_data_cb_t draw_data_cb;
    imgui_animlib_draw_cb_t draw_cb;
    imgui_animlib_file_menu_item_cb_t file_menu_item_cb;
    imgui_animlib_draw_menu_cb_t draw_menu_cb;
    imgui_animlib_play_cb_t play_cb;
    imgui_animlib_seek_cb_t seek_cb;
};

void menu_item_cb(const char* option_name)
{
    printf("menu item: %s\n", option_name);
}

void empty_fun()
{
}

void imgui_animlib_set_cb(ImGuiAnimlibState* state, AnimlibCallbackId cb_id, void* cb)
{
    switch (cb_id)
    {
        case AnimlibCallbackId_Menuitem:
            printf("set menu item callback\n");
            state->file_menu_item_cb = (imgui_animlib_file_menu_item_cb_t)cb;
            break;
        case AnimlibCallbackId_DrawMenu:
            state->draw_menu_cb = (imgui_animlib_draw_menu_cb_t)cb;
            break;
        case AnimlibCallbackId_Play:
            state->play_cb = (imgui_animlib_play_cb_t)cb;
            break;
        case AnimlibCallbackId_Seek:
            state->seek_cb = (imgui_animlib_seek_cb_t)cb;
            break;
        default:
            printf("unknown callback id: %d\n", cb_id);
            break;
    }
}

ImGuiAnimlibState* imgui_animlib_init(imgui_animlib_draw_data_cb_t draw_data_cb, imgui_animlib_draw_cb_t draw_cb, const char *resources_path)
{
    auto state = new ImGuiAnimlibState();
    auto ctx = ImGui::CreateContext();
    ImGui::SetCurrentContext(ctx);
    state->ctx = ctx;
    state->draw_data_cb = draw_data_cb;
    state->draw_cb = draw_cb;
    state->file_menu_item_cb = menu_item_cb;
    state->draw_menu_cb = empty_fun;
    state->play_cb = empty_fun;
    state->seek_cb = (imgui_animlib_seek_cb_t)empty_fun;

    auto& io = ImGui::GetIO();
    io.ConfigFlags |= ImGuiConfigFlags_DockingEnable;
    io.ConfigFlags |= ImGuiConfigFlags_NavEnableKeyboard;
    io.ConfigFlags |= ImGuiConfigFlags_NavEnableGamepad;

    ImGui::StyleColorsDark();

    io.Fonts->AddFontDefault();
    io.Fonts->Build();

    ImFontConfig config;
    config.MergeMode = true;
#define ICON_MIN_FA 0xf000
#define ICON_MAX_FA 0xf2e0
    static const ImWchar icon_ranges[] = { ICON_MIN_FA, ICON_MAX_FA, 0 };
    auto path = std::string(resources_path) + "/fontawesome-webfont.ttf";
    io.Fonts->AddFontFromFileTTF(path.c_str(), 13.0f, &config, icon_ranges);

    auto& style = ImGui::GetStyle();
    style.WindowRounding = 0.0f;
    style.Colors[ImGuiCol_WindowBg].w = 1.0f;

    return state;
}

void imgui_animlib_drag_drop_item(const char* item)
{
    ImGui::Selectable(item);
    ImGuiDragDropFlags src_flags = 0;
    src_flags |= ImGuiDragDropFlags_SourceNoDisableHover;
    src_flags |= ImGuiDragDropFlags_SourceNoHoldToOpenOthers;
    if (ImGui::BeginDragDropSource(src_flags))
    {
        if (src_flags & ImGuiDragDropFlags_SourceNoPreviewTooltip)
        {
            ImGui::Text("%s", item);
        }
        ImGui::SetDragDropPayload("DND_DEMO_CELL", item, strlen(item) + 1);
        ImGui::EndDragDropSource();
    }
}

void imgui_animlib_main_dock(ImGuiAnimlibState* state)
{
    ImVec2 menu_size = ImVec2(0.0f, 0.0f);

    bool show = true;

    ImGui::SetCurrentContext(state->ctx);
    auto vp = ImGui::GetMainViewport();
    auto window_flags = ImGuiWindowFlags_MenuBar | ImGuiWindowFlags_NoDocking;
    ImGui::SetNextWindowPos(vp->WorkPos);
    ImGui::SetNextWindowSize(vp->WorkSize);
    ImGui::SetNextWindowViewport(vp->ID);

    ImGui::PushStyleVar(ImGuiStyleVar_WindowRounding, 0.0f);
    ImGui::PushStyleVar(ImGuiStyleVar_WindowBorderSize, 0.0f);
    window_flags |= ImGuiWindowFlags_NoTitleBar | ImGuiWindowFlags_NoCollapse | ImGuiWindowFlags_NoResize | ImGuiWindowFlags_NoMove;
    window_flags |= ImGuiWindowFlags_NoBringToFrontOnFocus | ImGuiWindowFlags_NoNavFocus;

    ImGui::PushStyleVar(ImGuiStyleVar_WindowPadding, ImVec2(0.0f, 0.0f));
    ImGui::Begin("MainDockSpace", &show, window_flags);
    ImGui::PopStyleVar(3);

    auto dock_node_flags = ImGuiDockNodeFlags_PassthruCentralNode;
    uint32_t dockspace_id = 0;
    auto& io = ImGui::GetIO();
    if (io.ConfigFlags & ImGuiConfigFlags_DockingEnable)
    {
        dockspace_id = ImGui::GetID("MyDockSpace");
        ImGui::DockSpace(dockspace_id, ImVec2(0.0f, 0.0f), dock_node_flags);
    }
    else
    {
        printf("no docking\n");
        return;
    }

    state->draw_menu_cb(); 

    menu_size = ImGui::GetWindowSize();

    //test_window();

    ImGui::End();

    ImGui::SetNextWindowDockID(dockspace_id, ImGuiCond_FirstUseEver);
}

ImVec4 calculate_view_area(int x, int y, int width, int height, double view_aspect)
{
    // calculate scene view "bars" (aspect ratio correction)
    double aspect = (double)width / (double)height;
    int w, h;
    int wShrink = 0;
    int hShrink = 0;
    if (aspect > view_aspect) { // too wide, vertical bars
        int nw = (int)(height * view_aspect);
        wShrink = (int)width - nw;
        if((wShrink&1) == 1) // make even to please the pixel-perfect OCD people
            wShrink++;
    } else if (aspect < view_aspect) { // too tall, horizontal bars
        int nh = (int)((double)width / view_aspect);
        hShrink = (int)height - nh;
        if((hShrink&1) == 1)
            hShrink++;
    }
    w = (int)width - wShrink;
    h = (int)height - hShrink;
    return ImVec4((float)(wShrink/2) , y, w, h);
}

void test_window()
{
    ImGui::ShowDemoWindow();
    ImGui::Begin("Test");
    ImGui::Text("Hello, world!");
    ImGui::Button(ICON_FA_PLAY, ImVec2(50.0f, 20.0f));
    ImGui::SameLine();
    static float stest = 0.0f;
    Seekbar("##seekbar", &stest, 0.0f, 1.0f);
    ImGui::End();
}

IRect imgui_animlib_scene_window(ImGuiAnimlibState* state, double view_aspect, int texture_handle, bool playing, float cursor, float cursor_max)
{
    ImGui::SetCurrentContext(state->ctx);

    auto window_flags = ImGuiWindowFlags_DockNodeHost | ImGuiWindowFlags_NoScrollbar | ImGuiWindowFlags_NoScrollWithMouse;
    /*
    // no resize
    window_flags |= ImGuiWindowFlags_NoResize;
    // no title bar
    window_flags |= ImGuiWindowFlags_NoTitleBar;
    // no collapse
    window_flags |= ImGuiWindowFlags_NoCollapse;
    // no move
    window_flags |= ImGuiWindowFlags_NoMove;*/

    ImGui::Begin("Scene", nullptr, window_flags);

    //auto size = ImGui::GetWindowContentRegionMax() - ImGui::GetWindowContentRegionMin();
    auto wcrmax = ImGui::GetWindowContentRegionMax();
    auto wcrmin = ImGui::GetWindowContentRegionMin();
    ImVec2 size(wcrmax.x - wcrmin.x, wcrmax.y - wcrmin.y);
    auto fpadding = ImGui::GetStyle().FramePadding;
    auto iispacing = ImGui::GetStyle().ItemInnerSpacing;

    //auto playText = "Play";
    //auto pauseText = "Pause";
    auto combinedText = "PlayPause";
    auto btnSize = ImGui::CalcTextSize(combinedText);

    float verticalOffset = btnSize.y + 4.0f*fpadding.y + 2.0f*iispacing.y;
    size.y -= verticalOffset;

    auto area = calculate_view_area(0, verticalOffset, size.x, size.y, view_aspect);
    size.x = area.z;
    size.y = area.w;

    static float stest;
    if (ImGui::Button(playing ? ICON_FA_PAUSE : ICON_FA_PLAY, ImVec2(50.0f, 20.0f)))
    {
        state->play_cb();
    }
    ImGui::SameLine();
    if(Seekbar("##seekbar", &cursor, 0.0f, cursor_max))
    {
        state->seek_cb(cursor);
    }

    auto pos = (ImGui::GetWindowSize() - size) * 0.5f;
    pos.y += verticalOffset/2.0f;
    ImGui::SetCursorPos(pos);
    auto spos = ImGui::GetCursorScreenPos();
    ImGui::Image((void*)(intptr_t)texture_handle, size, ImVec2(0.0f, 1.0f), ImVec2(1.0f, 0.0f));

    ImGui::End();

    return IRect{ (int)spos.x, (int)spos.y, (int)size.x, (int)size.y };
}

void imgui_animlib_set_font_texture(ImGuiAnimlibState* state, int texture)
{
    ImGui::SetCurrentContext(state->ctx);
    auto& io = ImGui::GetIO();
    io.Fonts->SetTexID((void*)(intptr_t)texture);
}

void imgui_animlib_shutdown(ImGuiAnimlibState* state)
{
    ImGui::DestroyContext(state->ctx);
    delete state;
}

void imgui_animlib_get_fonts_texture_data(ImGuiAnimlibState* state, unsigned char** out_pixels, int* out_width, int* out_height, int* out_bytes_per_pixel)
{
    ImGui::SetCurrentContext(state->ctx);
    auto& io = ImGui::GetIO();
    io.Fonts->GetTexDataAsRGBA32(out_pixels, out_width, out_height, out_bytes_per_pixel);
}

void imgui_animlib_update(ImGuiAnimlibState* state, int width, int height, float dt, float mouseX, float mouseY, bool left, bool right, bool middle, float scrollDelta)
{
    ImGui::SetCurrentContext(state->ctx);
    auto& io = ImGui::GetIO();
    io.DisplaySize = ImVec2(width, height);
    io.DisplayFramebufferScale = ImVec2(1.0f, 1.0f);
    io.DeltaTime = dt;
    io.MousePos = ImVec2(mouseX, mouseY);
    io.MouseDown[0] = left;
    io.MouseDown[1] = right;
    io.MouseDown[2] = middle;
    io.MouseWheel = scrollDelta;
}

void imgui_animlib_begin_frame(ImGuiAnimlibState* state)
{
    ImGui::SetCurrentContext(state->ctx);

    ImGui::NewFrame();
    imgui_animlib_main_dock(state);
    //ImGui::ShowDemoWindow();
}

void imgui_animlib_end_frame(ImGuiAnimlibState* state)
{
    ImGui::SetCurrentContext(state->ctx);
    ImGui::EndFrame();

    ImGui::Render();

    auto draw_data = ImGui::GetDrawData();

    // fill vertex and index buffers
    for (int i = 0; i < draw_data->CmdListsCount; i++)
    {
        const ImDrawList* cmd_list = draw_data->CmdLists[i];
        state->draw_data_cb(cmd_list->VtxBuffer.Data, cmd_list->VtxBuffer.Size, sizeof(ImDrawVert), cmd_list->IdxBuffer.Data, cmd_list->IdxBuffer.Size, sizeof(ImDrawIdx));
    }

    // draw
    int vtx_offset = 0;
    int idx_offset = 0;
    for (int i = 0; i < draw_data->CmdListsCount; i++)
    {
        const ImDrawList* cmd_list = draw_data->CmdLists[i];
        for (int ci = 0; ci < cmd_list->CmdBuffer.Size; ci++)
        {
            auto pcmd = &cmd_list->CmdBuffer[ci];
            auto texture = (int)(intptr_t)pcmd->TextureId;
            auto clipX1 = pcmd->ClipRect.x;
            auto clipY1 = pcmd->ClipRect.y;
            auto clipX2 = pcmd->ClipRect.z;
            auto clipY2 = pcmd->ClipRect.w;
            state->draw_cb(idx_offset, pcmd->ElemCount, vtx_offset, texture, clipX1, clipY1, clipX2, clipY2);
            idx_offset += pcmd->ElemCount;
        }
        vtx_offset += cmd_list->VtxBuffer.Size;
    }
}

void test()
{
}
