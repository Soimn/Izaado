TYPEDEF_FUNC(void, renderer_begin_frame, u32 width, u32 height);
TYPEDEF_FUNC(void, renderer_end_frame);

global renderer_begin_frame Renderer_BeginFrame;
global renderer_end_frame Renderer_EndFrame;

internal void Win32_ErrorPrompt(const char* message, ...);

#define WGL_CONTEXT_MAJOR_VERSION_ARB             0x2091
#define WGL_CONTEXT_MINOR_VERSION_ARB             0x2092
#define WGL_CONTEXT_LAYER_PLANE_ARB               0x2093
#define WGL_CONTEXT_FLAGS_ARB                     0x2094
#define WGL_CONTEXT_PROFILE_MASK_ARB              0x9126

#define WGL_CONTEXT_DEBUG_BIT_ARB                 0x0001
#define WGL_CONTEXT_FORWARD_COMPATIBLE_BIT_ARB    0x0002

#define WGL_CONTEXT_CORE_PROFILE_BIT_ARB          0x00000001
#define WGL_CONTEXT_COMPATIBILITY_PROFILE_BIT_ARB 0x00000002

#define WGL_DRAW_TO_WINDOW_ARB                    0x2001
#define WGL_ACCELERATION_ARB                      0x2003
#define WGL_SUPPORT_OPENGL_ARB                    0x2010
#define WGL_DOUBLE_BUFFER_ARB                     0x2011
#define WGL_PIXEL_TYPE_ARB                        0x2013

#define WGL_TYPE_RGBA_ARB                         0x202B
#define WGL_FULL_ACCELERATION_ARB                 0x2027

#define WGL_FRAMEBUFFER_SRGB_CAPABLE_ARB          0x20A9

#define WGL_RED_BITS_ARB                          0x2015
#define WGL_GREEN_BITS_ARB                        0x2017
#define WGL_BLUE_BITS_ARB                         0x2019
#define WGL_ALPHA_BITS_ARB                        0x201B
#define WGL_DEPTH_BITS_ARB                        0x2022

typedef BOOL wglChoosePixelFormatARBfunc(HDC hdc, const int* piAttribIList, const FLOAT* pfAttribFList, UINT nMaxFormats, int* piFormats,
                                         UINT* nNumFormats);
typedef HGLRC wglCreateContextAttribsARBfunc(HDC hDC, HGLRC hshareContext, const int *attribList);
typedef char* wglGetExtensionsStringEXTfunc(void);

bool
Win32_InitOpenGL(HINSTANCE instance, HWND window_handle)
{
    bool succeeded = false;
    
    HDC window_dc = GetDC(window_handle);
    
    wglChoosePixelFormatARBfunc* wglChoosePixelFormatARB       = 0;
    wglCreateContextAttribsARBfunc* wglCreateContextAttribsARB = 0;
    wglGetExtensionsStringEXTfunc* wglGetExtensionsStringEXT   = 0;
    
    WNDCLASSA window_class = {
        .lpfnWndProc   = &DefWindowProcA,
        .hInstance     = instance,
        .lpszClassName = "CeresWGLLoader",
    };
    
    if (RegisterClassA(&window_class))
    {
        
        HWND dummy_handle = CreateWindowExA(0, window_class.lpszClassName, "Ceres", 0,
                                            CW_USEDEFAULT, CW_USEDEFAULT, CW_USEDEFAULT, CW_USEDEFAULT,
                                            0, 0, window_class.hInstance, 0);
        
        if (dummy_handle != INVALID_HANDLE_VALUE)
        {
            
            HDC dummy_dc = GetDC(dummy_handle);
            
            PIXELFORMATDESCRIPTOR pixel_format = {
                .nSize      = sizeof(PIXELFORMATDESCRIPTOR),
                .nVersion   = 1,
                .dwFlags    = PFD_SUPPORT_OPENGL | PFD_DRAW_TO_WINDOW | PFD_DOUBLEBUFFER,
                .iPixelType = PFD_TYPE_RGBA,
                .cColorBits = 32,
                .cAlphaBits = 8,
                .cDepthBits = 24,
                //.iLayerType = PFD_MAIN_PLANE,
            };
            
            i32 picked_pixel_format_index = ChoosePixelFormat(dummy_dc, &pixel_format);
            
            PIXELFORMATDESCRIPTOR picked_pixel_format;
            SetPixelFormat(dummy_dc, picked_pixel_format_index, &picked_pixel_format);
            
            HGLRC gl_context = wglCreateContext(dummy_dc);
            if (gl_context != 0 && wglMakeCurrent(dummy_dc, gl_context))
            {
                wglChoosePixelFormatARB    = (wglChoosePixelFormatARBfunc*)   wglGetProcAddress("wglChoosePixelFormatARB");
                wglCreateContextAttribsARB = (wglCreateContextAttribsARBfunc*)wglGetProcAddress("wglCreateContextAttribsARB");
                wglGetExtensionsStringEXT  = (wglGetExtensionsStringEXTfunc*) wglGetProcAddress("wglGetExtensionsStringEXT");
            }
            
            wglMakeCurrent(0, 0);
            wglDeleteContext(gl_context);
            ReleaseDC(dummy_handle, dummy_dc);
            DestroyWindow(dummy_handle);
        }
    }
    
    UnregisterClassA("CeresWGLLoader", instance);
    
    if (wglChoosePixelFormatARB != 0 && wglChoosePixelFormatARB != 0 && wglGetExtensionsStringEXT != 0)
    {
        for (char* scan = wglGetExtensionsStringEXT(); scan != 0;)
        {
            while (*scan == ' ') ++scan;
            
            if (*scan == 0) break;
            else
            {
                String extension = { .data = (u8*)scan };
                
                while (*scan != ' ') ++scan, ++extension.size;
                
                // TODO: check for extensions
                // StringCompare(extension, STRING("extension string"))
            }
        }
        
        int attributes[] = {
            WGL_DRAW_TO_WINDOW_ARB, GL_TRUE,
            WGL_ACCELERATION_ARB, WGL_FULL_ACCELERATION_ARB,
            WGL_SUPPORT_OPENGL_ARB, GL_TRUE,
            WGL_DOUBLE_BUFFER_ARB, GL_TRUE,
            WGL_PIXEL_TYPE_ARB, WGL_TYPE_RGBA_ARB,
            //WGL_FRAMEBUFFER_SRGB_CAPABLE_ARB, GL_TRUE,
            0,
        };
        
        u32 pick_count                = 0;
        int picked_pixel_format_index = 0;
        PIXELFORMATDESCRIPTOR picked_pixel_format = {0};
        if (wglChoosePixelFormatARB(window_dc, attributes, 0, 1, &picked_pixel_format_index, &pick_count) && pick_count == 1 &&
            SetPixelFormat(window_dc, picked_pixel_format_index, &picked_pixel_format))
        {
            int context_attribs[] =
            {
                WGL_CONTEXT_MAJOR_VERSION_ARB, 3,
                WGL_CONTEXT_MINOR_VERSION_ARB, 3,
                WGL_CONTEXT_FLAGS_ARB, WGL_CONTEXT_FORWARD_COMPATIBLE_BIT_ARB
#if IZ_DEBUG
                | WGL_CONTEXT_DEBUG_BIT_ARB
#endif
                ,
                WGL_CONTEXT_PROFILE_MASK_ARB, WGL_CONTEXT_CORE_PROFILE_BIT_ARB,
                0,
            };
            
            HGLRC context = wglCreateContextAttribsARB(window_dc, 0, context_attribs);
            
            if (context != 0 && wglMakeCurrent(window_dc, context))
            {
                
                bool all_pointers_are_valid = true;
#define X(return_vals, name, ...) name = (name##func)wglGetProcAddress(#name); all_pointers_are_valid = (all_pointers_are_valid && name);
                CORE_OPENGL_FUNCTION_LIST()
#undef X
                
                typedef BOOL wglSwapIntervalEXTfunc(int interval);
                wglSwapIntervalEXTfunc* wglSwapIntervalEXT = (wglSwapIntervalEXTfunc*)wglGetProcAddress("wglSwapIntervalEXT");
                all_pointers_are_valid = (all_pointers_are_valid && wglSwapIntervalEXT);
                
                if (all_pointers_are_valid)
                {
                    wglSwapIntervalEXT(1);
                    
                    glEnable(GL_BLEND);
                    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
                    
                    succeeded = true;
                }
            }
        }
    }
    
    return succeeded;
}

void
Win32_GLBeginFrame(u32 width, u32 height)
{
    Renderer->width  = width;
    Renderer->height = height;
    
    glViewport(0, 0, (GLsizei)width, (GLsizei)height);
    
    glClearColor(0, 0, 0, 1);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
}

void
Win32_GLEndFrame()
{
    SwapBuffers(wglGetCurrentDC());
}

internal bool
Win32_RendererSetup(HINSTANCE instance, HWND window_handle)
{
    bool succeeded = false;
    
    Renderer_State* state = &Platform->renderer_state;
    Renderer = state;
    
    if (Win32_InitOpenGL(instance, window_handle) && GLRIM_Setup())
    {
        Platform->PushLine          = &GLRIM_PushLine;
        Platform->PushRect          = &GLRIM_PushRect;
        Platform->PushFilledRect    = &GLRIM_PushFilledRect;
        Platform->PushCircle        = &GLRIM_PushCircle;
        Platform->PushFilledCircle  = &GLRIM_PushFilledCircle;
        Platform->PushText          = &GLRIM_PushText;
        Platform->PushLineZ         = &GLRIM_PushLineZ;
        Platform->PushRectZ         = &GLRIM_PushRectZ;
        Platform->PushFilledRectZ   = &GLRIM_PushFilledRectZ;
        Platform->PushCircleZ       = &GLRIM_PushCircleZ;
        Platform->PushFilledCircleZ = &GLRIM_PushFilledCircleZ;
        Platform->PushTextZ         = &GLRIM_PushTextZ;
        
        Renderer_BeginFrame = &Win32_GLBeginFrame;
        Renderer_EndFrame   = &Win32_GLEndFrame;
        
        succeeded = true;
    }
    
    else
    {
        Win32_ErrorPrompt("Failed to initialize OpenGL");
    }
    
    return succeeded;
}