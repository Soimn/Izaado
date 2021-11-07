#include "GL/gl.h"

typedef char GLchar;
typedef imm GLsizeiptr;
typedef imm GLintptr;

#define CORE_OPENGL_FUNCTION_LIST()                                                                                                                                \
X(void, glBindFramebuffer, GLenum target, GLuint framebuffer)                                                                                                  \
X(void, glGenFramebuffers, GLsizei n, GLuint *framebuffers)                                                                                                    \
X(void, glFramebufferTexture2D, GLenum target, GLenum attachment, GLenum textarget, GLuint texture, GLint level)                                               \
X(GLenum, glCheckFramebufferStatus, GLenum target)                                                                                                             \
X(void, glBlitFramebuffer, GLint, GLint, GLint, GLint, GLint, GLint, GLint, GLint dstY1, GLbitfield mask, GLenum filter)                                       \
X(void, glAttachShader, GLuint program, GLuint shader)                                                                                                         \
X(void, glCompileShader, GLuint shader)                                                                                                                        \
X(GLuint, glCreateProgram, void)                                                                                                                               \
X(GLuint, glCreateShader, GLenum type)                                                                                                                         \
X(void, glLinkProgram, GLuint program)                                                                                                                         \
X(void, glShaderSource, GLuint shader, GLsizei count, GLchar **string, GLint *length)                                                                          \
X(void, glUseProgram, GLuint program)                                                                                                                          \
X(void, glGetProgramInfoLog, GLuint program, GLsizei bufSize, GLsizei *length, GLchar *infoLog)                                                                \
X(void, glGetShaderInfoLog, GLuint shader, GLsizei bufSize, GLsizei *length, GLchar *infoLog)                                                                  \
X(void, glGetShaderiv, GLuint shader, GLenum pname, GLint *params)                                                                                             \
X(void, glValidateProgram, GLuint program)                                                                                                                     \
X(void, glGetProgramiv, GLuint program, GLenum pname, GLint *params)                                                                                           \
X(GLint, glGetUniformLocation, GLuint program, const GLchar *name)                                                                                             \
X(void, glUniform4fv, GLint location, GLsizei count, const GLfloat *value)                                                                                     \
X(void, glUniformMatrix4fv, GLint location, GLsizei count, GLboolean transpose, const GLfloat *value)                                                          \
X(void, glUniform1i, GLint location, GLint v0)                                                                                                                 \
X(void, glUniform1f, GLint location, GLfloat v0)                                                                                                               \
X(void, glUniform2f, GLint location, GLfloat v0, GLfloat v1)                                                                                                   \
X(void, glUniform3f, GLint location, GLfloat v0, GLfloat v1, GLfloat v2)                                                                                       \
X(void, glUniform4f, GLint location, GLfloat v0, GLfloat v1, GLfloat v2, GLfloat v3)                                                                           \
X(void, glEnableVertexAttribArray, GLuint index)                                                                                                               \
X(void, glDisableVertexAttribArray, GLuint index)                                                                                                              \
X(GLint, glGetAttribLocation, GLuint program, const GLchar *name)                                                                                              \
X(void, glVertexAttribPointer, GLuint index, GLint size, GLenum type, GLboolean normalized, GLsizei stride, const void *pointer)                               \
X(void, glVertexAttribIPointer, GLuint index, GLint size, GLenum type, GLsizei stride, const void *pointer)                                                    \
X(void, glBindVertexArray, GLuint array)                                                                                                                       \
X(void, glGenVertexArrays, GLsizei n, GLuint *arrays)                                                                                                          \
X(void, glBindBuffer, GLenum target, GLuint buffer)                                                                                                            \
X(void, glGenBuffers, GLsizei n, GLuint *buffers)                                                                                                              \
X(void, glBufferData, GLenum target, GLsizeiptr size, const void *data, GLenum usage)                                                                          \
X(void, glActiveTexture, GLenum texture)                                                                                                                       \
X(void, glDeleteProgram, GLuint program)                                                                                                                       \
X(void, glDeleteShader, GLuint shader)                                                                                                                         \
X(void, glDeleteFramebuffers, GLsizei n, const GLuint *framebuffers)                                                                                           \
X(void, glDrawBuffers, GLsizei n, const GLenum *bufs)                                                                                                          \
X(void, glTexImage3D, GLenum, GLint, GLint, GLsizei, GLsizei height, GLsizei depth, GLint border, GLenum format, GLenum type, const void *pixels)              \
X(void, glTexSubImage3D, GLenum, GLint, GLint, GLint, GLint, GLsizei width, GLsizei height, GLsizei depth, GLenum format, GLenum type, const void *pixels)     \
X(void, glDrawElementsBaseVertex, GLenum mode, GLsizei count, GLenum type, const void *indices, GLint basevertex)                                              \

#define X(return_vals, name, ...) typedef return_vals APIENTRY name##func(__VA_ARGS__);
CORE_OPENGL_FUNCTION_LIST()
#undef X

#define X(return_vals, name, ...) global name##func* name = 0;
CORE_OPENGL_FUNCTION_LIST()
#undef X

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
#define X(return_vals, name, ...) name = (name##func*)wglGetProcAddress(#name); all_pointers_are_valid = (all_pointers_are_valid && name);
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

#define GL_ARRAY_BUFFER                   0x8892
#define GL_STATIC_DRAW                    0x88E4
#define GL_FRAGMENT_SHADER                0x8B30
#define GL_VERTEX_SHADER                  0x8B31
#define GL_COMPILE_STATUS                 0x8B81
#define GL_LINK_STATUS                    0x8B82
#define GL_VALIDATE_STATUS                0x8B83

global GLuint GLRIM_CircleProgram;
global GLuint GLRIM_RectProgram;
global GLuint GLRIM_VAO;

internal bool
GLRIM_Setup()
{
    GLchar* circle_vertex_shader_code =
        "#version 450\n"
        "\n"
        "out vec2 uv;\n"
        "out float t;\n"
        "out vec3 c;\n"
        "\n"
        "layout(location = 0) in vec3 position;\n"
        "layout(location = 1) uniform mat4 transform;\n"
        "layout(location = 2) uniform vec3 color;\n"
        "layout(location = 3) uniform float thickness;\n"
        "\n"
        "void\n"
        "main()\n"
        "{\n"
        "gl_Position = transform * vec4(position, 1.0);\n"
        "uv          = position.xy;\n"
        "t           = thickness;\n"
        "c           = color;\n"
        "}\n";
    
    GLchar* circle_fragment_shader_code =
        "#version 450\n"
        "\n"
        "out vec4 frag_color;\n"
        "\n"
        "in vec2 uv;\n"
        "in float t;\n"
        "in vec3 c;\n"
        "\n"
        "void\n"
        "main()\n"
        "{\n"
        "float fade = 0.008;\n"
        "float sdf = 1.0 - length(uv);\n"
        "float result = min(smoothstep(0.0, fade, sdf), 1.0 - smoothstep(t - fade, t, sdf));\n"
        "\n"
        "frag_color = vec4(c, result);\n"
        "}\n";
    
    GLchar* rect_vertex_shader_code =
        "#version 450\n"
        "\n"
        "out vec3 c;\n"
        "\n"
        "layout(location = 0) in vec3 position;\n"
        "layout(location = 1) uniform mat4 transform;\n"
        "layout(location = 2) uniform vec3 color;\n"
        "\n"
        "void\n"
        "main()\n"
        "{\n"
        "gl_Position = transform * vec4(position, 1.0);\n"
        "c           = color;\n"
        "}\n";
    
    GLchar* rect_fragment_shader_code =
        "#version 450\n"
        "\n"
        "out vec4 frag_color;\n"
        "\n"
        "in vec3 c;\n"
        "\n"
        "void\n"
        "main()\n"
        "{\n"
        "frag_color = vec4(c, 1.0);\n"
        "}\n";
    
    bool success = false;
    
    do
    {
        GLint status;
        
        GLRIM_CircleProgram = glCreateProgram();
        
        GLuint vertex = glCreateShader(GL_VERTEX_SHADER);
        glShaderSource(vertex, 1, &circle_vertex_shader_code, 0);
        glCompileShader(vertex);
        
        glGetShaderiv(vertex, GL_COMPILE_STATUS, &status);
        if (!status) break;
        
        GLuint fragment = glCreateShader(GL_FRAGMENT_SHADER);
        glShaderSource(fragment, 1, &circle_fragment_shader_code, 0);
        glCompileShader(fragment);
        
        glGetShaderiv(fragment, GL_COMPILE_STATUS, &status);
        if (!status) break;
        
        glAttachShader(GLRIM_CircleProgram, vertex);
        glAttachShader(GLRIM_CircleProgram, fragment);
        
        glLinkProgram(GLRIM_CircleProgram);
        
        glGetProgramiv(GLRIM_CircleProgram, GL_LINK_STATUS, &status);
        if (!status) break;
        
        glValidateProgram(GLRIM_CircleProgram);
        glGetProgramiv(GLRIM_CircleProgram, GL_VALIDATE_STATUS, &status);
        if (!status) break;
        
        glDeleteShader(vertex);
        glDeleteShader(fragment);
        
        
        
        GLRIM_RectProgram = glCreateProgram();
        
        vertex = glCreateShader(GL_VERTEX_SHADER);
        glShaderSource(vertex, 1, &rect_vertex_shader_code, 0);
        glCompileShader(vertex);
        
        glGetShaderiv(vertex, GL_COMPILE_STATUS, &status);
        if (!status) break;
        
        fragment = glCreateShader(GL_FRAGMENT_SHADER);
        glShaderSource(fragment, 1, &rect_fragment_shader_code, 0);
        glCompileShader(fragment);
        
        glGetShaderiv(fragment, GL_COMPILE_STATUS, &status);
        if (!status) break;
        
        glAttachShader(GLRIM_RectProgram, vertex);
        glAttachShader(GLRIM_RectProgram, fragment);
        
        glLinkProgram(GLRIM_RectProgram);
        
        glGetProgramiv(GLRIM_RectProgram, GL_LINK_STATUS, &status);
        if (!status) break;
        
        glValidateProgram(GLRIM_RectProgram);
        glGetProgramiv(GLRIM_RectProgram, GL_VALIDATE_STATUS, &status);
        if (!status) break;
        
        glDeleteShader(vertex);
        glDeleteShader(fragment);
        
        f32 vertecies[] = {
            1.0, 1.0, 0.0,
            -1.0, 1.0, 0.0,
            -1.0, -1.0, 0.0,
            -1.0, -1.0, 0.0,
            1.0, -1.0, 0.0,
            1.0, 1.0, 0.0,
        };
        
        glGenVertexArrays(1, &GLRIM_VAO);
        glBindVertexArray(GLRIM_VAO);
        
        GLuint vbo;
        glGenBuffers(1, &vbo);
        glBindBuffer(GL_ARRAY_BUFFER, vbo);
        glBufferData(GL_ARRAY_BUFFER, sizeof(vertecies), vertecies, GL_STATIC_DRAW);
        glVertexAttribPointer(0, 3, GL_FLOAT, false, 0, 0);
        glEnableVertexAttribArray(0);
        
        success = true;
    } while (0);
    
    return success;
}

void
GLRIM_PushLine(V2 p0, V2 p1, f32 line_thickness, V3 color)
{
    V2 center = {(p0.x + p1.x) / 2, (p0.y + p1.y) / 2};
    
    V2 p01         = V2_Sub(p1, p0);
    f32 p01_length = V2_Length(p01);
    
    // NOTE: simplified (with WolframAlpha) from a = atan(p01.y / p01.x), sin_a = sin(a), cos_a = cos(a)
    f32 sin_a = p01.y / p01_length;
    f32 cos_a = p01.x / p01_length;
    
    f32 half_width  = p01_length / 2;
    f32 half_height = line_thickness / 2;
    
    M4 transform = {
        .e = {
            Renderer->aspect_ratio * half_width * cos_a, half_width * sin_a, 0, 0,
            -Renderer->aspect_ratio * half_height * sin_a, half_height * cos_a, 0, 0,
            0, 0, 1, 0,
            Renderer->aspect_ratio * center.x, center.y, 0, 1,
        }
    };
    
    glUseProgram(GLRIM_RectProgram);
    glUniformMatrix4fv(1, 1, false, transform.e);
    glUniform3f(2, color.x, color.y, color.z);
    glBindVertexArray(GLRIM_VAO);
    glDrawArrays(GL_TRIANGLES, 0, 6);
}

void
GLRIM_PushFilledRect(Rect rect, f32 angle, V3 color)
{
    V2 center = {(rect.min.x + rect.max.x) / 2, (rect.min.y + rect.max.y) / 2};
    
    f32 half_width  = (rect.max.x - rect.min.x) / 2;
    f32 half_height = (rect.max.y - rect.min.y) / 2;
    
    f32 sin_a = Sin(angle);
    f32 cos_a = Cos(angle);
    
    M4 transform = {
        .e = {
            Renderer->aspect_ratio * cos_a * half_width, sin_a * half_width, 0, 0,
            Renderer->aspect_ratio * -sin_a * half_height, cos_a * half_height, 0, 0,
            0, 0, 1, 0,
            Renderer->aspect_ratio * center.x, center.y, 0, 1,
        }
    };
    
    
    glUseProgram(GLRIM_RectProgram);
    glUniformMatrix4fv(1, 1, false, transform.e);
    glUniform3f(2, color.x, color.y, color.z);
    glBindVertexArray(GLRIM_VAO);
    glDrawArrays(GL_TRIANGLES, 0, 6);
}

void
GLRIM_PushRect(Rect rect, f32 angle, f32 line_thickness, V3 color)
{
    V2 center = {(rect.min.x + rect.max.x) / 2, (rect.min.y + rect.max.y) / 2};
    
    f32 width  = rect.max.x - rect.min.x;
    f32 height = rect.max.y - rect.min.y;
    
    f32 sin_a = Sin(angle);
    f32 cos_a = Cos(angle);
    
    M4 transform = {
        .e = {
            cos_a * width, sin_a * width, 0, 0,
            -sin_a * height, cos_a * height, 0, 0,
            0, 0, 1, 0,
            center.x, center.y, 0, 1,
        }
    };
    
    V2 p0 = M4_Transform(transform, (V4){-0.5f, -0.5f, 0, 1}).xy;
    V2 p1 = M4_Transform(transform, (V4){ 0.5f, -0.5f, 0, 1}).xy;
    V2 p2 = M4_Transform(transform, (V4){ 0.5f,  0.5f, 0, 1}).xy;
    V2 p3 = M4_Transform(transform, (V4){-0.5f,  0.5f, 0, 1}).xy;
    
    GLRIM_PushLine(p0, p1, line_thickness, color);
    GLRIM_PushLine(p1, p2, line_thickness, color);
    GLRIM_PushLine(p2, p3, line_thickness, color);
    GLRIM_PushLine(p3, p0, line_thickness, color);
    
    GLRIM_PushFilledRect(RectangleFromPosScale(p0, Vec2(line_thickness, line_thickness)), angle, color);
    GLRIM_PushFilledRect(RectangleFromPosScale(p1, Vec2(line_thickness, line_thickness)), angle, color);
    GLRIM_PushFilledRect(RectangleFromPosScale(p2, Vec2(line_thickness, line_thickness)), angle, color);
    GLRIM_PushFilledRect(RectangleFromPosScale(p3, Vec2(line_thickness, line_thickness)), angle, color);
}

void
GLRIM_PushCircle(V2 center, f32 radius, f32 line_thickness, V3 color)
{
    f32 scale_factor = 1 + line_thickness / (2 * radius);
    
    M4 transform = {
        .e = {
            Renderer->aspect_ratio * scale_factor * radius, 0, 0, 0,
            0, scale_factor * radius, 0, 0,
            0, 0, 1, 0,
            Renderer->aspect_ratio * center.x, center.y, 0, 1
        }
    };
    
    glUseProgram(GLRIM_CircleProgram);
    glUniformMatrix4fv(1, 1, false, transform.e);
    glUniform3f(2, color.x, color.y, color.z);
    glUniform1f(3, (line_thickness / radius) / (1 + line_thickness / (2 * radius)));
    glBindVertexArray(GLRIM_VAO);
    glDrawArrays(GL_TRIANGLES, 0, 6);
}

void
GLRIM_PushFilledCircle(V2 center, f32 radius, V3 color)
{
    M4 transform = {
        .e = {
            Renderer->aspect_ratio * radius, 0, 0, 0,
            0, radius, 0, 0,
            0, 0, 1, 0,
            Renderer->aspect_ratio * center.x, center.y, 0, 1
        }
    };
    
    glUseProgram(GLRIM_CircleProgram);
    glUniformMatrix4fv(1, 1, false, transform.e);
    glUniform3f(2, color.x, color.y, color.z);
    glUniform1f(3, 3.0);
    glBindVertexArray(GLRIM_VAO);
    glDrawArrays(GL_TRIANGLES, 0, 6);
}

void
GLRIM_PushText()
{
}

void
GL_BeginFrame(imm width, imm height)
{
    Renderer->aspect_ratio = (f32)height / (imm)width;
    
    glViewport(0, 0, (GLsizei)width, (GLsizei)height);
    
    glClearColor(0, 0, 0, 1);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
}

void
GL_EndFrame()
{
    SwapBuffers(wglGetCurrentDC());
}