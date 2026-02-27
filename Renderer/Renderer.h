#ifndef RENDERER_H
#define RENDERER_H

#include "../Common/Window.h"
#include "../Math/Math.h"

struct Renderer
{
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

void R_Clear(Renderer*r, Vector color);
void R_Present(Renderer*r);

#endif // RENDERER_H
