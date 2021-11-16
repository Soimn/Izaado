#include "iz_platform.h"

void
GameTick(Platform_Data* platform)
{
    Platform = platform;
    Renderer = &platform->renderer_state;
    
    Renderer->PushRect(Rect_FromPosScale((V2){-1.0f, 0}, (V2){0.3f, 0.3f}), 0, 0.075f, (V3){1, 1, 1});
    Renderer->PushText(Rect_FromPosSize((V2){-1.0f, -0.5f}, (V2){1.0f, 0.16f}), 0, STRING("Hello World"), (V3){1, 1, 1});
}