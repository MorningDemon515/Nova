#ifdef _WIN32
#include <windows.h>
#endif // _WIN32

#include <stdio.h>
#include "Engine.h"

#include "../Math/Math.h"

int main(int argc, char *argv[])
{
    InitEngine();

    Window* w;
    w = W_Create(800, 600);
    W_SetTitle(w, "Nova");

    Renderer* r;
    r = R_Create(w, 32, 24, 8);

    Matrix m = {
    1.0f, 0.0f, 0.0f, 0.0f,
    0.0f, 1.0f ,0.0f, 0.0f,
    0.0f, 0.0f, 1.0f, 0.0f,
    1.0f, 2.0f, 3.0f, 1.0f
    };

    Vector v= { 0.0f, 0.0f, 0.0f, 1.0f };
    PrintVec(VecMulMat(v.data, m.data));

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

            R_Clear(r, 0.3f, 0.5f, 0.2f);

            R_Present(r);

        }
        #endif // _WIN32
    }

    R_Close(r);
    W_Close(w);
    QuitEngine();
    return 0;
}
