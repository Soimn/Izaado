#include "iz_platform.h"

void
GameTick(Platform_Data* platform)
{
    Platform = platform;
    Renderer = &platform->renderer_state;
    
    Renderer->PushRect(RectangleFromPosScale((V2){0, 0}, (V2){0.3f, 0.3f}), 0, 0.075f, (V3){1, 1, 1});
}