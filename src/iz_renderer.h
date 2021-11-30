TYPEDEF_FUNC(void, rim_push_line, V2 p0, V2 p1, f32 line_thickness, V3 color);
TYPEDEF_FUNC(void, rim_push_rect, Rect rect, f32 angle, f32 line_thickness, V3 color);
TYPEDEF_FUNC(void, rim_push_filled_rect, Rect rect, f32 angle, V3 color);
TYPEDEF_FUNC(void, rim_push_circle, V2 center, f32 radius, f32 line_thickness, V3 color);
TYPEDEF_FUNC(void, rim_push_filled_circle, V2 center, f32 radius, V3 color);
TYPEDEF_FUNC(void, rim_push_text, Rect text_box, f32 angle, String text, V3 color);

TYPEDEF_FUNC(void, rim_push_line_z, V2 p0, V2 p1, f32 line_thickness, V3 color, f32 z);
TYPEDEF_FUNC(void, rim_push_rect_z, Rect rect, f32 angle, f32 line_thickness, V3 color, f32 z);
TYPEDEF_FUNC(void, rim_push_filled_rect_z, Rect rect, f32 angle, V3 color, f32 z);
TYPEDEF_FUNC(void, rim_push_circle_z, V2 center, f32 radius, f32 line_thickness, V3 color, f32 z);
TYPEDEF_FUNC(void, rim_push_filled_circle_z, V2 center, f32 radius, V3 color, f32 z);
TYPEDEF_FUNC(void, rim_push_text_z, Rect text_box, f32 angle, String text, V3 color, f32 z);

typedef struct Renderer_State
{
    u32 width;
    u32 height;
} Renderer_State;