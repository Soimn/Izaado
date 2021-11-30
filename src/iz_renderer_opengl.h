#include "GL/gl.h"

typedef i8 GLchar;
typedef imm GLintptr;
typedef imm GLsizeiptr;

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

#define X(return_val, name, ...) TYPEDEF_FUNC(return_val, name##func, __VA_ARGS__);
CORE_OPENGL_FUNCTION_LIST()
#undef X

#define X(return_vals, name, ...) global name##func name = 0;
CORE_OPENGL_FUNCTION_LIST()
#undef X

#define GL_ARRAY_BUFFER                   0x8892
#define GL_STATIC_DRAW                    0x88E4
#define GL_FRAGMENT_SHADER                0x8B30
#define GL_VERTEX_SHADER                  0x8B31
#define GL_COMPILE_STATUS                 0x8B81
#define GL_LINK_STATUS                    0x8B82
#define GL_VALIDATE_STATUS                0x8B83

global GLuint GLRIM_CircleProgram;
global GLuint GLRIM_RectProgram;
global GLuint GLRIM_TextProgram;
global GLuint GLRIM_VAO;
global GLuint GLRIM_DebugFontTexture;

internal bool
GLRIM_Setup()
{
    GLchar* circle_vertex_shader_code =
        "#version 450\n"
        "\n"
        "out vec2 uv;\n"
        "out vec3 c;\n"
        "out float t;\n"
        "\n"
        "layout(location = 0) in vec3 position;\n"
        "layout(location = 1) uniform mat4 matrix;\n"
        "\n"
        "void\n"
        "main()\n"
        "{\n"
        "mat4 transform = matrix;\n"
        "transform[2] = vec4(0, 0, 1, 0);\n"
        "gl_Position = transform * vec4(position, 1.0);\n"
        "uv          = position.xy;\n"
        "c           = matrix[2].xyz;\n"
        "t           = matrix[2].w;\n"
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
        "layout(location = 1) uniform mat4 matrix;\n"
        "\n"
        "void\n"
        "main()\n"
        "{\n"
        "mat4 transform = matrix;\n"
        "transform[2].xyzw = vec4(0, 0, 1, 0);\n"
        "gl_Position = transform * vec4(position, 1.0);\n"
        "c           = matrix[2].xyz;\n"
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
    
    GLchar* text_vertex_shader_code =
        "#version 450\n"
        "\n"
        "out vec2 uv;\n"
        "out vec3 c;\n"
        "\n"
        "layout(location = 0) in vec3 position;\n"
        "layout(location = 1) uniform mat4 matrix;\n"
        "\n"
        "void\n"
        "main()\n"
        "{\n"
        "mat4 transform = matrix;\n"
        "transform[0].zw  = vec2(0);\n"
        "transform[1].zw  = vec2(0);\n"
        "transform[2].xyz = vec3(0, 0, 1);\n"
        "gl_Position = transform * vec4(position, 1.0);\n"
        "\n"
        "uv = position.xy * matrix[0].zw + matrix[1].zw;\n"
        "c  = matrix[2].xyz;\n"
        "}\n";
    
    GLchar* text_fragment_shader_code =
        "#version 450\n"
        "\n"
        "out vec4 frag_color;\n"
        "\n"
        "in vec2 uv;\n"
        "in vec3 c;\n"
        "uniform sampler2D glyph_map;\n"
        "\n"
        "void\n"
        "main()\n"
        "{\n"
        "frag_color = texture(glyph_map, uv) * vec4(c, 1.0);\n"
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
        
        
        
        GLRIM_TextProgram = glCreateProgram();
        
        vertex = glCreateShader(GL_VERTEX_SHADER);
        glShaderSource(vertex, 1, &text_vertex_shader_code, 0);
        glCompileShader(vertex);
        
        glGetShaderiv(vertex, GL_COMPILE_STATUS, &status);
        if (!status) break;
        
        fragment = glCreateShader(GL_FRAGMENT_SHADER);
        glShaderSource(fragment, 1, &text_fragment_shader_code, 0);
        glCompileShader(fragment);
        
        glGetShaderiv(fragment, GL_COMPILE_STATUS, &status);
        if (!status) break;
        
        glAttachShader(GLRIM_TextProgram, vertex);
        glAttachShader(GLRIM_TextProgram, fragment);
        
        glLinkProgram(GLRIM_TextProgram);
        
        glGetProgramiv(GLRIM_TextProgram, GL_LINK_STATUS, &status);
        if (!status) break;
        
        glValidateProgram(GLRIM_TextProgram);
        glGetProgramiv(GLRIM_TextProgram, GL_VALIDATE_STATUS, &status);
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
        
        // TODO: check for opengl errors in the code below
        glGenVertexArrays(1, &GLRIM_VAO);
        glBindVertexArray(GLRIM_VAO);
        
        GLuint vbo;
        glGenBuffers(1, &vbo);
        glBindBuffer(GL_ARRAY_BUFFER, vbo);
        glBufferData(GL_ARRAY_BUFFER, sizeof(vertecies), vertecies, GL_STATIC_DRAW);
        glVertexAttribPointer(0, 3, GL_FLOAT, false, 0, 0);
        glEnableVertexAttribArray(0);
        
        bool successfully_loaded_debug_font = false;
        
        Memory_Arena_Marker marker = Arena_BeginTempMemory(Platform->transient_memory);
        
        String debug_font_file_contents;
        if (Platform->ReadEntireFile(STRING("debug/debug_fontmap.tga"), Platform->transient_memory, 0, &debug_font_file_contents))
        {
            Targa_Header header;
            if (Targa_ReadHeader(debug_font_file_contents, &header))
            {
                ASSERT(header.width == 160 && header.height == 160 && header.depth == 32 &&
                       header.image_format == TargaImageFormat_UncompressedTrueColor);
                
                glGenTextures(1, &GLRIM_DebugFontTexture);
                glBindTexture(GL_TEXTURE_2D, GLRIM_DebugFontTexture);
                
                glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
                glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
                
                glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, 160, 160, 0, GL_RGBA, GL_UNSIGNED_BYTE, header.data);
                
                successfully_loaded_debug_font = true;
            }
        }
        
        Arena_EndTempMemory(Platform->transient_memory, marker);
        
        if (!successfully_loaded_debug_font) break;
        
        success = true;
    } while (0);
    
    return success;
}

void
GLRIM_PushLineZ(V2 p0, V2 p1, f32 line_thickness, V3 color, f32 z)
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
            half_width * cos_a, half_width * sin_a, 0, 0,
            -half_height * sin_a, half_height * cos_a, 0, 0,
            0, 0, 1, 0,
            center.x, center.y, z, 1,
        }
    };
    
    // NOTE: color info is packed into the matrix and extracted in the vertex shader
    transform.k.xyz = color;
    
    glUseProgram(GLRIM_RectProgram);
    glUniformMatrix4fv(1, 1, false, transform.e);
    glBindVertexArray(GLRIM_VAO);
    glDrawArrays(GL_TRIANGLES, 0, 6);
}

void
GLRIM_PushFilledRectZ(Rect rect, f32 angle, V3 color, f32 z)
{
    V2 center = Rect_Center(rect);
    
    f32 half_width  = Rect_Width(rect)  / 2;
    f32 half_height = Rect_Height(rect) / 2;
    
    f32 sin_a = Sin(angle);
    f32 cos_a = Cos(angle);
    
    M4 transform = {
        .e = {
            cos_a * half_width, sin_a * half_width, 0, 0,
            -sin_a * half_height, cos_a * half_height, 0, 0,
            0, 0, 1, 0,
            center.x, center.y, z, 1,
        }
    };
    
    // NOTE: color info is packed into the matrix and extracted in the vertex shader
    transform.k.xyz = color;
    
    glUseProgram(GLRIM_RectProgram);
    glUniformMatrix4fv(1, 1, false, transform.e);
    glBindVertexArray(GLRIM_VAO);
    glDrawArrays(GL_TRIANGLES, 0, 6);
}

void
GLRIM_PushRectZ(Rect rect, f32 angle, f32 line_thickness, V3 color, f32 z)
{
    V2 center = Rect_Center(rect);
    
    f32 width  = Rect_Width(rect);
    f32 height = Rect_Height(rect);
    
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
    
    GLRIM_PushLineZ(p0, p1, line_thickness, color, z);
    GLRIM_PushLineZ(p1, p2, line_thickness, color, z);
    GLRIM_PushLineZ(p2, p3, line_thickness, color, z);
    GLRIM_PushLineZ(p3, p0, line_thickness, color, z);
    
    GLRIM_PushFilledRectZ(Rect_FromPosScale(p0, Vec2(line_thickness, line_thickness)), angle, color, z);
    GLRIM_PushFilledRectZ(Rect_FromPosScale(p1, Vec2(line_thickness, line_thickness)), angle, color, z);
    GLRIM_PushFilledRectZ(Rect_FromPosScale(p2, Vec2(line_thickness, line_thickness)), angle, color, z);
    GLRIM_PushFilledRectZ(Rect_FromPosScale(p3, Vec2(line_thickness, line_thickness)), angle, color, z);
}

void
GLRIM_PushCircleZ(V2 center, f32 radius, f32 line_thickness, V3 color, f32 z)
{
    f32 scale_factor = 1 + line_thickness / (2 * radius);
    
    M4 transform = {
        .e = {
            scale_factor * radius, 0, 0, 0,
            0, scale_factor * radius, 0, 0,
            0, 0, 1, 0,
            center.x, center.y, z, 1
        }
    };
    
    // NOTE: color and thickness information is packed into the matrix and extracted in the vertex shader
    transform.k.xyz = color;
    transform.k.w   = (line_thickness / radius) / (1 + line_thickness / (2 * radius));
    
    glUseProgram(GLRIM_CircleProgram);
    glUniformMatrix4fv(1, 1, false, transform.e);
    glBindVertexArray(GLRIM_VAO);
    glDrawArrays(GL_TRIANGLES, 0, 6);
}

void
GLRIM_PushFilledCircleZ(V2 center, f32 radius, V3 color, f32 z)
{
    M4 transform = {
        .e = {
            radius, 0, 0, 0,
            0, radius, 0, 0,
            0, 0, 1, 0,
            center.x, center.y, z, 1
        }
    };
    
    // NOTE: color and thickness information is packed into the matrix and extracted in the vertex shader
    transform.k.xyz = color;
    transform.k.w   = 3.0f;
    
    glUseProgram(GLRIM_CircleProgram);
    glUniformMatrix4fv(1, 1, false, transform.e);
    glBindVertexArray(GLRIM_VAO);
    glDrawArrays(GL_TRIANGLES, 0, 6);
}

void
GLRIM_PushTextZ(Rect text_box, f32 angle, String text, V3 color, f32 z)
{
    f32 text_size = Rect_Height(text_box);
    if (text.size * text_size > Rect_Width(text_box))
    {
        text_size = Rect_Width(text_box) / text.size;
    }
    
    glUseProgram(GLRIM_TextProgram);
    glBindTexture(GL_TEXTURE_2D, GLRIM_DebugFontTexture);
    glBindVertexArray(GLRIM_VAO);
    
    V2 advancement = (V2){text_box.min.x, text_box.min.y + text_size / 2};
    for (umm i = 0; i < text.size; ++i)
    {
        f32 character_width   = 1.0f;
        f32 character_end_pad = 0.0f;
        
        f32 half_width  = character_width * text_size / 2;
        f32 half_height = text_size                   / 2;
        
        V2 translation = V2_Add(advancement, (V2){half_width, Rect_Height(text_box) / 2 - half_height});
        
        f32 sin_a = Sin(angle);
        f32 cos_a = Cos(angle);
        
        M4 transform = {
            .e = {
                cos_a * half_width, sin_a * half_width, 0, 0,
                -sin_a * half_height, cos_a * half_height, 0, 0,
                0, 0, 1, 0,
                translation.x, translation.y, z, 1,
            }
        };
        
        // NOTE: color and uv adjustment info is packed into the matrix and extracted in the vertex shader
        transform.i.zw = V2_Scale((V2){character_width / 2, 0.5f}, 1 / 16.0f);
        transform.j.zw = V2_Scale(V2_Add((V2){character_width / 2, 0.5f}, (V2){(f32)(text.data[i] % 16), (f32)((255 - text.data[i]) / 16)}), 1 / 16.0f);
        transform.k.xyz = color;
        
        glUniformMatrix4fv(1, 1, false, transform.e);
        glDrawArrays(GL_TRIANGLES, 0, 6);
        
        advancement.x += (character_width + character_end_pad) * text_size;
    }
}

void
GLRIM_PushLine(V2 p0, V2 p1, f32 line_thickness, V3 color)
{
    GLRIM_PushLineZ(p0, p1, line_thickness, color, -1);
}

void
GLRIM_PushFilledRect(Rect rect, f32 angle, V3 color)
{
    GLRIM_PushFilledRectZ(rect, angle, color, -1);
}

void
GLRIM_PushRect(Rect rect, f32 angle, f32 line_thickness, V3 color)
{
    GLRIM_PushRectZ(rect, angle, line_thickness, color, -1);
}

void
GLRIM_PushCircle(V2 center, f32 radius, f32 line_thickness, V3 color)
{
    GLRIM_PushCircleZ(center, radius, line_thickness, color, -1);
}

void
GLRIM_PushFilledCircle(V2 center, f32 radius, V3 color)
{
    GLRIM_PushFilledCircleZ(center, radius, color, -1);
}

void
GLRIM_PushText(Rect text_box, f32 angle, String text, V3 color)
{
    GLRIM_PushTextZ(text_box, angle, text, color, -1);
}