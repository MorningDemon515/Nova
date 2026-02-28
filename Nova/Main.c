#ifdef _WIN32
#include <windows.h>
#endif // _WIN32

#include <stdio.h>
#include <stdlib.h>

#include "Engine.h"

#include <glad/glad.h>

int main(int argc, char *argv[])
{
    InitEngine();

    Window* w;
    w = W_Create(800, 600);
    W_SetTitle(w, "Nova");

    Renderer* r;
    r = R_Create(w, 32, 24, 8);

    Rect* r1 = R_CreateRect(r, Vec4(0.0f, 0.0f, 100.0f, 100.0f), Vec3(1.0f, 0.0f, 0.0f));

    MSG msg;
    while(1)
    {
        #ifdef _WIN32
        if(PeekMessage(&msg,0,0,0,PM_REMOVE))
        {
            if(msg.message == WM_QUIT)
                break;

            TranslateMessage(&msg);
            DispatchMessage(&msg);
        }
        else
        {
            W_Update(w);
            R_Update(r);

            R_Clear(r, Vec3(0.2f, 0.5f, 0.3f));

            R_DrawRect(r1);

            R_Present(r);

        }
        #endif // _WIN32
    }

    R_DeleteRect(r1);

    R_Close(r);
    W_Close(w);
    QuitEngine();
    return 0;
}
