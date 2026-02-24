#ifndef WINDOW_H
#define WINDOW_H

#ifdef _WIN32
#include <windows.h>
#endif //_WIN32

struct Window
{
    int x, y;
    int width, height;

    const char* title;
    int show;
    #ifdef _WIN32
    HWND hwnd;
    HINSTANCE hInstance;
    #endif //_WIN32
};

typedef struct Window Window;

Window* W_Create( int width, int height);
void W_Close(Window* w);

void W_SetTitle(Window* w, const char* title);
void W_SetSize(Window* w, int w_, int h_);
void W_SetPos(Window* w, int x, int y);

void W_Update(Window* w);

int W_GetWidth(Window* w);
int W_GetHeight(Window* w);

#ifdef _WIN32
HWND W_GetHandle(Window* w);
#endif //_WIN32

#endif // WINDOW_H
