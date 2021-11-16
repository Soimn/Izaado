TYPEDEF_FUNC(void, rim_push_line, V2 p0, V2 p1, f32 line_thickness, V3 color);
TYPEDEF_FUNC(void, rim_push_rect, Rect rect, f32 angle, f32 line_thickness, V3 color);
TYPEDEF_FUNC(void, rim_push_filled_rect, Rect rect, f32 angle, V3 color);
TYPEDEF_FUNC(void, rim_push_circle, V2 center, f32 radius, f32 line_thickness, V3 color);
TYPEDEF_FUNC(void, rim_push_filled_circle, V2 center, f32 radius, V3 color);
TYPEDEF_FUNC(void, rim_push_text, Rect text_box, f32 angle, String text, V3 color);

typedef struct Renderer_State
{
    rim_push_line PushLine;
    rim_push_rect PushRect;
    rim_push_filled_rect PushFilledRect;
    rim_push_circle PushCircle;
    rim_push_filled_circle PushFilledCircle;
    rim_push_text PushText;
    
    f32 aspect_ratio;
} Renderer_State;