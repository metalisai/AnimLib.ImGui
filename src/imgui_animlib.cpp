#define IMGUI_DEFINE_MATH_OPERATORS
#include "imgui.h"

#include <cstdio>
#include <cstdint>
#include "imgui_animlib.h"
#include <string>

#define ICON_FA_HEART "\uf004"
#define ICON_FA_PLAY "\uf04b"
#define ICON_FA_PAUSE "\uf04c"

enum OpenTKKeyKey
{
	/// <summary>A key outside the known keys.</summary>
	OpenTKKey_Unknown = 0,
	/// <summary>The left shift key.</summary>
	OpenTKKey_ShiftLeft = 1,
	/// <summary>The left shift key (equivalent to ShiftLeft).</summary>
	OpenTKKey_LShift = 1,
	/// <summary>The right shift key.</summary>
	OpenTKKey_ShiftRight = 2,
	/// <summary>The right shift key (equivalent to ShiftRight).</summary>
	OpenTKKey_RShift = 2,
	/// <summary>The left control key.</summary>
	OpenTKKey_ControlLeft = 3,
	/// <summary>The left control key (equivalent to ControlLeft).</summary>
	OpenTKKey_LControl = 3,
	/// <summary>The right control key.</summary>
	OpenTKKey_ControlRight = 4,
	/// <summary>The right control key (equivalent to ControlRight).</summary>
	OpenTKKey_RControl = 4,
	/// <summary>The left alt key.</summary>
	OpenTKKey_AltLeft = 5,
	/// <summary>The left alt key (equivalent to AltLeft.</summary>
	OpenTKKey_LAlt = 5,
	/// <summary>The right alt key.</summary>
	OpenTKKey_AltRight = 6,
	/// <summary>The right alt key (equivalent to AltRight).</summary>
	OpenTKKey_RAlt = 6,
	/// <summary>The left win key.</summary>
	OpenTKKey_WinLeft = 7,
	/// <summary>The left win key (equivalent to WinLeft).</summary>
	OpenTKKey_LWin = 7,
	/// <summary>The right win key.</summary>
	OpenTKKey_WinRight = 8,
	/// <summary>The right win key (equivalent to WinRight).</summary>
	OpenTKKey_RWin = 8,
	/// <summary>The menu key.</summary>
	OpenTKKey_Menu = 9,
	/// <summary>The F1 key.</summary>
	OpenTKKey_F1 = 10,
	/// <summary>The F2 key.</summary>
	OpenTKKey_F2 = 11,
	/// <summary>The F3 key.</summary>
	OpenTKKey_F3 = 12,
	/// <summary>The F4 key.</summary>
	OpenTKKey_F4 = 13,
	/// <summary>The F5 key.</summary>
	OpenTKKey_F5 = 14,
	/// <summary>The F6 key.</summary>
	OpenTKKey_F6 = 15,
	/// <summary>The F7 key.</summary>
	OpenTKKey_F7 = 16,
	/// <summary>The F8 key.</summary>
	OpenTKKey_F8 = 17,
	/// <summary>The F9 key.</summary>
	OpenTKKey_F9 = 18,
	/// <summary>The F10 key.</summary>
	OpenTKKey_F10 = 19,
	/// <summary>The F11 key.</summary>
	OpenTKKey_F11 = 20,
	/// <summary>The F12 key.</summary>
	OpenTKKey_F12 = 21,
	/// <summary>The F13 key.</summary>
	OpenTKKey_F13 = 22,
	/// <summary>The F14 key.</summary>
	OpenTKKey_F14 = 23,
	/// <summary>The F15 key.</summary>
	OpenTKKey_F15 = 24,
	/// <summary>The F16 key.</summary>
	OpenTKKey_F16 = 25,
	/// <summary>The F17 key.</summary>
	OpenTKKey_F17 = 26,
	/// <summary>The F18 key.</summary>
	OpenTKKey_F18 = 27,
	/// <summary>The F19 key.</summary>
	OpenTKKey_F19 = 28,
	/// <summary>The F20 key.</summary>
	OpenTKKey_F20 = 29,
	/// <summary>The F21 key.</summary>
	OpenTKKey_F21 = 30,
	/// <summary>The F22 key.</summary>
	OpenTKKey_F22 = 31,
	/// <summary>The F23 key.</summary>
	OpenTKKey_F23 = 32,
	/// <summary>The F24 key.</summary>
	OpenTKKey_F24 = 33,
	/// <summary>The F25 key.</summary>
	OpenTKKey_F25 = 34,
	/// <summary>The F26 key.</summary>
	OpenTKKey_F26 = 35,
	/// <summary>The F27 key.</summary>
	OpenTKKey_F27 = 36,
	/// <summary>The F28 key.</summary>
	OpenTKKey_F28 = 37,
	/// <summary>The F29 key.</summary>
	OpenTKKey_F29 = 38,
	/// <summary>The F30 key.</summary>
	OpenTKKey_F30 = 39,
	/// <summary>The F31 key.</summary>
	OpenTKKey_F31 = 40,
	/// <summary>The F32 key.</summary>
	OpenTKKey_F32 = 41,
	/// <summary>The F33 key.</summary>
	OpenTKKey_F33 = 42,
	/// <summary>The F34 key.</summary>
	OpenTKKey_F34 = 43,
	/// <summary>The F35 key.</summary>
	OpenTKKey_F35 = 44,
	/// <summary>The up arrow key.</summary>
	OpenTKKey_Up = 45,
	/// <summary>The down arrow key.</summary>
	OpenTKKey_Down = 46,
	/// <summary>The left arrow key.</summary>
	OpenTKKey_Left = 47,
	/// <summary>The right arrow key.</summary>
	OpenTKKey_Right = 48,
	/// <summary>The enter key.</summary>
	OpenTKKey_Enter = 49,
	/// <summary>The escape key.</summary>
	OpenTKKey_Escape = 50,
	/// <summary>The space key.</summary>
	OpenTKKey_Space = 51,
	/// <summary>The tab key.</summary>
	OpenTKKey_Tab = 52,
	/// <summary>The backspace key.</summary>
	OpenTKKey_BackSpace = 53,
	/// <summary>The backspace key (equivalent to BackSpace).</summary>
	OpenTKKey_Back = 53,
	/// <summary>The insert key.</summary>
	OpenTKKey_Insert = 54,
	/// <summary>The delete key.</summary>
	OpenTKKey_Delete = 55,
	/// <summary>The page up key.</summary>
	OpenTKKey_PageUp = 56,
	/// <summary>The page down key.</summary>
	OpenTKKey_PageDown = 57,
	/// <summary>The home key.</summary>
	OpenTKKey_Home = 58,
	/// <summary>The end key.</summary>
	OpenTKKey_End = 59,
	/// <summary>The caps lock key.</summary>
	OpenTKKey_CapsLock = 60,
	/// <summary>The scroll lock key.</summary>
	OpenTKKey_ScrollLock = 61,
	/// <summary>The print screen key.</summary>
	OpenTKKey_PrintScreen = 62,
	/// <summary>The pause key.</summary>
	OpenTKKey_Pause = 63,
	/// <summary>The num lock key.</summary>
	OpenTKKey_NumLock = 64,
	/// <summary>The clear key (Keypad5 with NumLock disabled, on typical keyboards).</summary>
	OpenTKKey_Clear = 65,
	/// <summary>The sleep key.</summary>
	OpenTKKey_Sleep = 66,
	/// <summary>The keypad 0 key.</summary>
	OpenTKKey_Keypad0 = 67,
	/// <summary>The keypad 1 key.</summary>
	OpenTKKey_Keypad1 = 68,
	/// <summary>The keypad 2 key.</summary>
	OpenTKKey_Keypad2 = 69,
	/// <summary>The keypad 3 key.</summary>
	OpenTKKey_Keypad3 = 70,
	/// <summary>The keypad 4 key.</summary>
	OpenTKKey_Keypad4 = 71,
	/// <summary>The keypad 5 key.</summary>
	OpenTKKey_Keypad5 = 72,
	/// <summary>The keypad 6 key.</summary>
	OpenTKKey_Keypad6 = 73,
	/// <summary>The keypad 7 key.</summary>
	OpenTKKey_Keypad7 = 74,
	/// <summary>The keypad 8 key.</summary>
	OpenTKKey_Keypad8 = 75,
	/// <summary>The keypad 9 key.</summary>
	OpenTKKey_Keypad9 = 76,
	/// <summary>The keypad divide key.</summary>
	OpenTKKey_KeypadDivide = 77,
	/// <summary>The keypad multiply key.</summary>
	OpenTKKey_KeypadMultiply = 78,
	/// <summary>The keypad subtract key.</summary>
	OpenTKKey_KeypadSubtract = 79,
	/// <summary>The keypad minus key (equivalent to KeypadSubtract).</summary>
	OpenTKKey_KeypadMinus = 79,
	/// <summary>The keypad add key.</summary>
	OpenTKKey_KeypadAdd = 80,
	/// <summary>The keypad plus key (equivalent to KeypadAdd).</summary>
	OpenTKKey_KeypadPlus = 80,
	/// <summary>The keypad decimal key.</summary>
	OpenTKKey_KeypadDecimal = 81,
	/// <summary>The keypad period key (equivalent to KeypadDecimal).</summary>
	OpenTKKey_KeypadPeriod = 81,
	/// <summary>The keypad enter key.</summary>
	OpenTKKey_KeypadEnter = 82,
	/// <summary>The A key.</summary>
	OpenTKKey_A = 83,
	/// <summary>The B key.</summary>
	OpenTKKey_B = 84,
	/// <summary>The C key.</summary>
	OpenTKKey_C = 85,
	/// <summary>The D key.</summary>
	OpenTKKey_D = 86,
	/// <summary>The E key.</summary>
	OpenTKKey_E = 87,
	/// <summary>The F key.</summary>
	OpenTKKey_F = 88,
	/// <summary>The G key.</summary>
	OpenTKKey_G = 89,
	/// <summary>The H key.</summary>
	OpenTKKey_H = 90,
	/// <summary>The I key.</summary>
	OpenTKKey_I = 91,
	/// <summary>The J key.</summary>
	OpenTKKey_J = 92,
	/// <summary>The K key.</summary>
	OpenTKKey_K = 93,
	/// <summary>The L key.</summary>
	OpenTKKey_L = 94,
	/// <summary>The M key.</summary>
	OpenTKKey_M = 95,
	/// <summary>The N key.</summary>
	OpenTKKey_N = 96,
	/// <summary>The O key.</summary>
	OpenTKKey_O = 97,
	/// <summary>The P key.</summary>
	OpenTKKey_P = 98,
	/// <summary>The Q key.</summary>
	OpenTKKey_Q = 99,
	/// <summary>The R key.</summary>
	OpenTKKey_R = 100,
	/// <summary>The S key.</summary>
	OpenTKKey_S = 101,
	/// <summary>The T key.</summary>
	OpenTKKey_T = 102,
	/// <summary>The U key.</summary>
	OpenTKKey_U = 103,
	/// <summary>The V key.</summary>
	OpenTKKey_V = 104,
	/// <summary>The W key.</summary>
	OpenTKKey_W = 105,
	/// <summary>The X key.</summary>
	OpenTKKey_X = 106,
	/// <summary>The Y key.</summary>
	OpenTKKey_Y = 107,
	/// <summary>The Z key.</summary>
	OpenTKKey_Z = 108,
	/// <summary>The number 0 key.</summary>
	OpenTKKey_Number0 = 109,
	/// <summary>The number 1 key.</summary>
	OpenTKKey_Number1 = 110,
	/// <summary>The number 2 key.</summary>
	OpenTKKey_Number2 = 111,
	/// <summary>The number 3 key.</summary>
	OpenTKKey_Number3 = 112,
	/// <summary>The number 4 key.</summary>
	OpenTKKey_Number4 = 113,
	/// <summary>The number 5 key.</summary>
	OpenTKKey_Number5 = 114,
	/// <summary>The number 6 key.</summary>
	OpenTKKey_Number6 = 115,
	/// <summary>The number 7 key.</summary>
	OpenTKKey_Number7 = 116,
	/// <summary>The number 8 key.</summary>
	OpenTKKey_Number8 = 117,
	/// <summary>The number 9 key.</summary>
	OpenTKKey_Number9 = 118,
	/// <summary>The tilde key.</summary>
	OpenTKKey_Tilde = 119,
	/// <summary>The grave key (equivaent to Tilde).</summary>
	OpenTKKey_Grave = 119,
	/// <summary>The minus key.</summary>
	OpenTKKey_Minus = 120,
	/// <summary>The plus key.</summary>
	OpenTKKey_Plus = 121,
	/// <summary>The left bracket key.</summary>
	OpenTKKey_BracketLeft = 122,
	/// <summary>The left bracket key (equivalent to BracketLeft).</summary>
	OpenTKKey_LBracket = 122,
	/// <summary>The right bracket key.</summary>
	OpenTKKey_BracketRight = 123,
	/// <summary>The right bracket key (equivalent to BracketRight).</summary>
	OpenTKKey_RBracket = 123,
	/// <summary>The semicolon key.</summary>
	OpenTKKey_Semicolon = 124,
	/// <summary>The quote key.</summary>
	OpenTKKey_Quote = 125,
	/// <summary>The comma key.</summary>
	OpenTKKey_Comma = 126,
	/// <summary>The period key.</summary>
	OpenTKKey_Period = 127,
	/// <summary>The slash key.</summary>
	OpenTKKey_Slash = 128,
	/// <summary>The backslash key.</summary>
	OpenTKKey_BackSlash = 129,
	/// <summary>The secondary backslash key.</summary>
	OpenTKKey_NonUSBackSlash = 130,
	/// <summary>Indicates the last available keyboard key.</summary>
	OpenTKKey_LastKey = 131
};

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

    io.KeyMap[ImGuiKey_Tab] = OpenTKKey_Tab;
    io.KeyMap[ImGuiKey_LeftArrow] = OpenTKKey_Left;
    io.KeyMap[ImGuiKey_RightArrow] = OpenTKKey_Right;
    io.KeyMap[ImGuiKey_UpArrow] = OpenTKKey_Up;
    io.KeyMap[ImGuiKey_DownArrow] = OpenTKKey_Down;
    io.KeyMap[ImGuiKey_PageUp] = OpenTKKey_PageUp;
    io.KeyMap[ImGuiKey_PageDown] = OpenTKKey_PageDown;
    io.KeyMap[ImGuiKey_Home] = OpenTKKey_Home;
    io.KeyMap[ImGuiKey_End] = OpenTKKey_End;
    io.KeyMap[ImGuiKey_Delete] = OpenTKKey_Delete;
    io.KeyMap[ImGuiKey_Backspace] = OpenTKKey_Back;
    io.KeyMap[ImGuiKey_Enter] = OpenTKKey_Enter;
    io.KeyMap[ImGuiKey_Escape] = OpenTKKey_Escape;
    io.KeyMap[ImGuiKey_A] = OpenTKKey_A;
    io.KeyMap[ImGuiKey_C] = OpenTKKey_C;
    io.KeyMap[ImGuiKey_V] = OpenTKKey_V;
    io.KeyMap[ImGuiKey_X] = OpenTKKey_X;
    io.KeyMap[ImGuiKey_Y] = OpenTKKey_Y;
    io.KeyMap[ImGuiKey_Z] = OpenTKKey_Z;
    io.KeyMap[ImGuiKey_Space] = OpenTKKey_Space;

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
