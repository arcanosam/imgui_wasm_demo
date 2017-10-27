#include <stdio.h>
#include <GLES2/gl2.h>
#include <SDL.h>
#include "emscripten.h"

typedef unsigned int ImU32;         // 32-bit unsigned integer (typically used to store packed colors)

struct ImVec2
{
    float x, y;
    ImVec2() { x = y = 0.0f; }
    ImVec2(float _x, float _y) { x = _x; y = _y; }
#ifdef IM_VEC2_CLASS_EXTRA          // Define constructor and implicit cast operators in imconfig.h to convert back<>forth from your math types and ImVec2.
    IM_VEC2_CLASS_EXTRA
#endif
};

struct ImDrawVert
{
    ImVec2  pos;
    ImVec2  uv;
    ImU32   col;
};

SDL_Window *window;

static int          g_ShaderHandle = 0, g_VertHandle = 0, g_FragHandle = 0;
static int          g_AttribLocationTex = 0, g_AttribLocationProjMtx = 0;
static int          g_AttribLocationPosition = 0, g_AttribLocationUV = 0, g_AttribLocationColor = 0;
static unsigned int g_VboHandle = 0, g_ElementsHandle = 0;

void mainloop(){

    GLint last_texture, last_array_buffer;
    glGetIntegerv(GL_TEXTURE_BINDING_2D, &last_texture);
    glGetIntegerv(GL_ARRAY_BUFFER_BINDING, &last_array_buffer);

    const GLchar *vertex_shader =
    "precision highp float;\n"
    "uniform mat4 ProjMtx;\n"
    "attribute vec2 Position;\n"
    "attribute vec2 UV;\n"
    "attribute vec4 Color;\n"
    "varying vec2 Frag_UV;\n"
    "varying vec4 Frag_Color;\n"
    "void main()\n"
    "{\n"
        "       Frag_UV = UV;\n"
        "       Frag_Color = Color;\n"
        "       gl_Position = ProjMtx * vec4(Position.xy,0,1);\n"
        "}\n";

    const GLchar* fragment_shader =
    "precision mediump float;\n"
    "uniform sampler2D Texture;\n"
    "varying vec2 Frag_UV;\n"
    "varying vec4 Frag_Color;\n"
    "void main()\n"
    "{\n"
        "       gl_FragColor = Frag_Color * texture2D( Texture, Frag_UV.st);\n"
        "}\n";

    g_ShaderHandle = glCreateProgram();

    g_VertHandle = glCreateShader(GL_VERTEX_SHADER);
    g_FragHandle = glCreateShader(GL_FRAGMENT_SHADER);

    glShaderSource(g_VertHandle, 1, &vertex_shader, 0);
    glShaderSource(g_FragHandle, 1, &fragment_shader, 0);

    glCompileShader(g_VertHandle);
    glCompileShader(g_FragHandle);

    glAttachShader(g_ShaderHandle, g_VertHandle);
    glAttachShader(g_ShaderHandle, g_FragHandle);

    glLinkProgram(g_ShaderHandle);

    g_AttribLocationTex = glGetUniformLocation(g_ShaderHandle, "Texture");
    g_AttribLocationProjMtx = glGetUniformLocation(g_ShaderHandle, "ProjMtx");
    g_AttribLocationPosition = glGetAttribLocation(g_ShaderHandle, "Position");
    g_AttribLocationUV = glGetAttribLocation(g_ShaderHandle, "UV");
    g_AttribLocationColor = glGetAttribLocation(g_ShaderHandle, "Color");

    glGenBuffers(1, &g_VboHandle);
    glGenBuffers(1, &g_ElementsHandle);

    glBindBuffer(GL_ARRAY_BUFFER, g_VboHandle);
    glEnableVertexAttribArray(g_AttribLocationPosition);
    glEnableVertexAttribArray(g_AttribLocationUV);
    glEnableVertexAttribArray(g_AttribLocationColor);

    #define OFFSETOF(TYPE, ELEMENT) ((size_t)&(((TYPE *)0)->ELEMENT))
    glVertexAttribPointer(g_AttribLocationPosition, 2, GL_FLOAT, GL_FALSE, sizeof(ImDrawVert), (GLvoid*)OFFSETOF(ImDrawVert, pos));
    glVertexAttribPointer(g_AttribLocationUV, 2, GL_FLOAT, GL_FALSE, sizeof(ImDrawVert), (GLvoid*)OFFSETOF(ImDrawVert, uv));
    glVertexAttribPointer(g_AttribLocationColor, 4, GL_UNSIGNED_BYTE, GL_TRUE, sizeof(ImDrawVert), (GLvoid*)OFFSETOF(ImDrawVert, col));
    #undef OFFSETOF

    // Restore modified GL state
    glBindTexture(GL_TEXTURE_2D, last_texture);
    glBindBuffer(GL_ARRAY_BUFFER, last_array_buffer);

    int w, h;
    int display_w, display_h;

    ImVec2 DisplaySize;

    SDL_GetWindowSize(window, &w, &h);

    SDL_GL_GetDrawableSize(window, &display_w, &display_h);

    DisplaySize = ImVec2((float)w, (float)h);

    // Rendering
    glViewport(0, 0, (int)DisplaySize.x, (int)DisplaySize.y);

    glClearColor(
        39.018,
        0.0470588281750679,
        0.5647059082984924,
        0.7843137979507446
    );

    glClear(GL_COLOR_BUFFER_BIT);

    SDL_GL_SwapWindow(window);
}

int main(int, char**){

    SDL_DisplayMode current;

    // Setup SDL
	if (SDL_Init(SDL_INIT_VIDEO) != 0)
	{
        printf("Error: %s\n", SDL_GetError());
        return -1;
	}

    // Setup window
	SDL_GL_SetAttribute(SDL_GL_DOUBLEBUFFER, 1);
	SDL_GL_SetAttribute(SDL_GL_DEPTH_SIZE, 24);
	SDL_GL_SetAttribute(SDL_GL_STENCIL_SIZE, 8);
	SDL_GL_SetAttribute(SDL_GL_CONTEXT_MAJOR_VERSION, 2);
	SDL_GL_SetAttribute(SDL_GL_CONTEXT_MINOR_VERSION, 2);

	SDL_GetCurrentDisplayMode(0, &current);

    window = SDL_CreateWindow("ImGui SDL2+OpenGL example", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, 1280, 720, SDL_WINDOW_OPENGL|SDL_WINDOW_RESIZABLE);

	SDL_GLContext glcontext = SDL_GL_CreateContext(window);

	emscripten_set_main_loop(mainloop, 0, 0);

    return 0;
}
