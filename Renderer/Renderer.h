#ifndef RENDERER_H
#define RENDERER_H

#include "../Common/Window.h"
#include "Shader.h"

struct Renderer
{
    Matrix proj;
    Window* w;
    #ifdef _WIN32
    HDC hdc;
    HGLRC hglrc;
    #endif // _WIN32
};

typedef struct Renderer Renderer;

Renderer* R_Create(Window* w,
                        unsigned int colorBits,
                        unsigned int depthBits,
                        unsigned int stencilBits);

void R_Close(Renderer* r);

void R_Update(Renderer* r);
void R_Clear(Renderer*r, Vector color);
void R_Present(Renderer*r);

struct Rect
{
    int x, y, w, h;
    Renderer* renderer;
    unsigned int VAO, VBO, EBO;
    Shader* shader;
};

typedef struct Rect Rect;

Rect* R_CreateRect(Renderer* r, Vector rect, Vector color);
void R_DeleteRect(Rect* r);
void R_DrawRect(Rect* r);

#endif // RENDERER_H
