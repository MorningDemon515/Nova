#include "Renderer.h"

#include <glad/glad.h>

#ifdef _WIN32
typedef int (WINAPI *CPFFunc)(HDC hdc,const PIXELFORMATDESCRIPTOR *ppfd);
typedef BOOL (WINAPI *SPFFunc)(HDC hdc,int format,const PIXELFORMATDESCRIPTOR *ppfd);
typedef BOOL (WINAPI *SBFunc)(HDC unnamedParaml);

static HMODULE gdiDLL;
#endif // _WIN32

Renderer* R_Create(Window* w,
                        unsigned int colorBits,
                        unsigned int depthBits,
                        unsigned int stencilBits)
{
    #ifdef _WIN32
    gdiDLL = LoadLibrary("gdi32.dll");

    HDC hdc = GetDC(w->hwnd);

    PIXELFORMATDESCRIPTOR pfd = {
        sizeof(PIXELFORMATDESCRIPTOR),    // size of this pfd
        1,                                // version number
        PFD_DRAW_TO_WINDOW |              // support window
        PFD_SUPPORT_OPENGL |              // support OpenGL
        PFD_DOUBLEBUFFER,                 // double buffered
        PFD_TYPE_RGBA,                    // RGBA type
        colorBits,                               // color depth
        0, 0, 0, 0, 0, 0,                 // color bits ignored
        0,                                // no alpha buffer
        0,                                // shift bit ignored
        0,                                // no accumulation buffer
        0, 0, 0, 0,                       // accum bits ignored
        depthBits,                               // z-buffer
        stencilBits,                                //stencil buffer
        0,                                // no auxiliary buffer
        PFD_MAIN_PLANE,                   // main layer
        0,                                // reserved
        0, 0, 0                           // layer masks ignored
    };

    CPFFunc CPF = (CPFFunc)GetProcAddress(gdiDLL, "ChoosePixelFormat");
    SPFFunc SPF = (SPFFunc)GetProcAddress(gdiDLL, "SetPixelFormat");

    int iPixelFormat = CPF(hdc, &pfd);
    SPF(hdc, iPixelFormat, &pfd);

    HGLRC hglrc = wglCreateContext(hdc);
    wglMakeCurrent(hdc, hglrc);

    gladLoadGL();
    #endif // _WIN32

    Renderer* r = (Renderer*)malloc(sizeof(Renderer));
    r->w = w;

    #ifdef _WIN32
    r->hdc = hdc;
    r->hglrc = hglrc;
    #endif // _WIN32

    return r;
}

void R_Close(Renderer* r)
{
    #ifdef _WIN32
    wglMakeCurrent(NULL, NULL);
    wglDeleteContext(r->hglrc);
    ReleaseDC(r->w->hwnd, r->hdc);

    FreeLibrary(gdiDLL);
    #endif //_WIN32
    free(r);
}

void R_Clear(Renderer*r, float red, float green, float blue)
{
    glClearColor(red, green, blue, 1.0f);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
}

void R_Present(Renderer*r)
{
    #ifdef _WIN32
    SBFunc SB = (SBFunc)GetProcAddress(gdiDLL, "SwapBuffers");
    SB(r->hdc);
    #endif // _WIN32
}
