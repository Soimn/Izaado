#include "iz_platform.h"
#include "iz_rg.h"

void
GameTick(Platform_Data* platform, V2 cursor_pos, String input_string, u32 mouse_button_state)
{
    Platform = platform;
    Renderer = &platform->renderer_state;
    
#if 0
    Renderer->PushRect(Rect_FromPosScale((V2){-1.0f, 0}, (V2){0.3f, 0.3f}), 0, 0.075f, (V3){1, 1, 1});
    Renderer->PushFilledRect(Rect_FromPosScale((V2){-1.0f, 0}, (V2){0.05f, 0.05f}), 0, (V3){1, 1, 1});
    
    Renderer->PushRect(Rect_FromPosScale((V2){-0.5f, 0}, (V2){0.3f, 0.3f}), 0, 0.075f, (V3){1, 1, 1});
    Renderer->PushFilledRect(Rect_FromPosScale((V2){-0.5f, 0}, (V2){0.05f, 0.05f}), 0, (V3){1, 1, 1});
    
    Renderer->PushText(Rect_FromPosSize((V2){-1.2f, -0.3f}, (V2){2.0f, 0.5f}), 0, STRING("Horny police has arrived !(*=*)."), (V3){1, 1, 1});
#endif
    
#if 0
    f32 step = 0.0001f;
    f32 x = -1.0f;
    f32 scale_factor = 5*PI32;
    while (x <= 1.0f)
    {
        f32 start = x;
        x += step;
        
        Renderer->PushFilledCircle((V2){start, Sin(start*scale_factor) / 2}, 0.002f, (V3){0.8f, 0.3f, 0.3f});
        Renderer->PushFilledCircle((V2){start, Cos(start*scale_factor) / 2}, 0.002f, (V3){0.3f, 0.3f, 0.8f});
        Renderer->PushFilledCircle((V2){start, Tan(start*scale_factor) / 2}, 0.002f, (V3){0.3f, 0.8f, 0.3f});
    }
#endif
}