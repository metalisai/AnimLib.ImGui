// windows
#ifdef _WIN32
#define EXPORT __declspec(dllexport)
#else
#define EXPORT
#endif

typedef void (*imgui_animlib_draw_data_cb_t)(void *vtx_data, int vtx_count, int vtx_size, void *idx_data, int idx_count, int idx_size);
typedef void (*imgui_animlib_draw_cb_t)(int i_offset, int i_count, int v_offset, int texture, float clipX1, float clipY1, float clipX2, float clipY2);

typedef void (*imgui_animlib_file_menu_item_cb_t)(const char* option_name);
typedef void (*imgui_animlib_draw_menu_cb_t)();
typedef void (*imgui_animlib_play_cb_t)();
typedef void (*imgui_animlib_seek_cb_t)(float value);

class ImGuiAnimlibState;

typedef struct IRect
{
    int x, y, w, h;
} IRect;

typedef enum AnimlibCallbackId
{
    AnimlibCallbackId_None = 0,
    AnimlibCallbackId_Menuitem = 1,
    AnimlibCallbackId_DrawMenu = 2,
    AnimlibCallbackId_Play = 3,
    AnimlibCallbackId_Seek = 5
} AnimlibCallbackId;


#ifdef __cplusplus
extern "C" {
#else 
#error fu
#endif

EXPORT ImGuiAnimlibState* imgui_animlib_init(imgui_animlib_draw_data_cb_t draw_data_cb, imgui_animlib_draw_cb_t draw_cb, const char *resources_path);
EXPORT void imgui_animlib_shutdown(ImGuiAnimlibState* state);
EXPORT void imgui_animlib_get_fonts_texture_data(ImGuiAnimlibState* state, unsigned char** out_pixels, int* out_width, int* out_height, int* out_bytes_per_pixel);
EXPORT void imgui_animlib_update(ImGuiAnimlibState* state, int width, int height, float dt, float mouseX, float mouseY, bool left, bool right, bool middle, float scrollDelta);
EXPORT void imgui_animlib_begin_frame(ImGuiAnimlibState* state);
EXPORT void imgui_animlib_end_frame(ImGuiAnimlibState* state);
EXPORT void imgui_animlib_set_font_texture(ImGuiAnimlibState* state, int texture);
EXPORT IRect imgui_animlib_scene_window(ImGuiAnimlibState* state, double view_aspect, int texture_handle, bool playing, float cursor, float cursor_max);
EXPORT void imgui_animlib_set_cb(ImGuiAnimlibState* state, AnimlibCallbackId cb_id, void* cb);

// imgui api
EXPORT bool imgui_animlib_begin(const char *name, bool *show, int wflags);
EXPORT void imgui_animlib_end();
EXPORT void imgui_animlib_text(const char *text);
EXPORT bool imgui_animlib_collapsing_header(const char *text);
EXPORT bool imgui_animlib_button(const char *text);
EXPORT void imgui_animlib_same_line();
EXPORT bool imgui_animlib_color_edit4(const char *label, float col[4]);
EXPORT bool imgui_animlib_input_text(const char *label, char *buf, unsigned int size);
EXPORT bool imgui_animlib_input_double(const char *label, double *val);
EXPORT ImVec2 imgui_animlib_get_mouse_pos();
EXPORT bool imgui_animlib_begin_drag_drop_target();
EXPORT void imgui_animlib_end_drag_drop_target();
EXPORT const void* imgui_animlib_accept_drag_drop_payload(const char *name);
EXPORT void imgui_animlib_set_next_window_size(ImVec2 size, int cond_flags);
EXPORT void imgui_animlib_columns(int count);
EXPORT void imgui_animlib_separator();
EXPORT void imgui_animlib_spacing();
EXPORT void imgui_animlib_push_style_var_float(int idx, float val);
EXPORT void imgui_animlib_push_style_var_float2(int idx, ImVec2 val);
EXPORT void imgui_animlib_pop_style_var(int count);
EXPORT bool imgui_animlib_begin_menu_bar();
EXPORT void imgui_animlib_end_menu_bar();
EXPORT bool imgui_animlib_begin_menu(const char *label);
EXPORT void imgui_animlib_end_menu();
EXPORT bool imgui_animlib_menu_item(const char *item);
EXPORT ImVec2 imgui_animlib_get_window_size();
EXPORT void imgui_animlib_push_style_color_u32(int idx, ImU32 col);
EXPORT void imgui_animlib_push_style_color_float4(int idx, struct ImVec4 const *col);
EXPORT void imgui_animlib_pop_style_color(int count);
EXPORT bool imgui_animlib_list_box(const char *label, int *current_item, const char* const items[], int items_count, int height_in_items);
EXPORT bool imgui_animlib_input_float(const char *label, float *v);
EXPORT bool imgui_animlib_input_float2(const char *label, float v[]);
EXPORT bool imgui_animlib_input_float3(const char *label, float v[]);
EXPORT bool imgui_animlib_is_mouse_clicked(int button, bool repeat);
EXPORT bool imgui_animlib_is_mouse_down(int button);
EXPORT bool imgui_animlib_begin_combo(const char *label, const char *preview_value, int flags);
EXPORT void imgui_animlib_end_combo();
EXPORT bool imgui_animlib_selectable(const char *label, bool *p_selected, int flags, const ImVec2 *size);
EXPORT void imgui_animlib_fg_circle_filled(ImVec2 screen_pos, float radius, ImU32 col);
EXPORT void imgui_animlib_fg_text(ImVec2 screen_pos, ImU32 col, const char *text_begin);
EXPORT void imgui_animlib_drag_drop_item(const char* item);

#ifdef __cplusplus
}
#endif

bool Seekbar(const char* label, float* v, float v_min, float v_max);
