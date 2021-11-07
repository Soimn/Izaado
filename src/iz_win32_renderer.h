#include "iz_win32_opengl.h"

typedef void (*renderer_begin_frame)(imm width, imm height);
typedef void (*renderer_end_frame)();

global renderer_begin_frame Renderer_BeginFrame;
global renderer_end_frame Renderer_EndFrame;

internal void Win32_ErrorPrompt(const char* message, ...);

internal bool
Renderer_Setup(HINSTANCE instance, HWND window_handle)
{
    bool succeeded = false;
    
    Renderer_State* state = &Platform->renderer_state;
    Renderer = state;
    
    if (Win32_InitOpenGL(instance, window_handle) && GLRIM_Setup())
    {
        state->PushLine         = &GLRIM_PushLine,
        state->PushRect         = &GLRIM_PushRect,
        state->PushFilledRect   = &GLRIM_PushFilledRect,
        state->PushCircle       = &GLRIM_PushCircle,
        state->PushFilledCircle = &GLRIM_PushFilledCircle,
        state->PushText         = &GLRIM_PushText,
        
        Renderer_BeginFrame = &GL_BeginFrame;
        Renderer_EndFrame   = &GL_EndFrame;
        
        succeeded = true;
    }
    
    else
    {
        Win32_ErrorPrompt("Failed to initialize OpenGL");
    }
    
    return succeeded;
}