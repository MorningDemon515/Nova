#ifndef RENDERER_H
#define RENDERER_H

#include "../Common/Window.h"

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

void R_Clear(Renderer*r, float red, float green, float blue);
void R_Present(Renderer*r);

#endif // RENDERER_H
