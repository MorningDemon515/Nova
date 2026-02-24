#include "Window.h"

#ifdef _WIN32
#define winClass "Nova Class"

LRESULT CALLBACK WndProc(HWND hwnd, UINT msg, WPARAM wParam, LPARAM lParam);

bool IsDarkThemeByColor() {
    DWORD value = 1;
    DWORD size = sizeof(DWORD);

    HKEY hKey;
    if (RegOpenKeyExA(
        HKEY_CURRENT_USER,
        "Software\\Microsoft\\Windows\\CurrentVersion\\Themes\\Personalize",
        0,
        KEY_READ,
        &hKey) == ERROR_SUCCESS)
    {
        RegQueryValueExA(
            hKey,
            "AppsUseLightTheme",
            NULL,
            NULL,
            (LPBYTE)&value,
            &size);

        RegCloseKey(hKey);
    }

    return value == 0;
}

typedef HRESULT (WINAPI *PDwmSetWindowAttribute)(HWND hwnd, DWORD dwAttribute, LPCVOID pvAttribute, DWORD cbAttribute);
void SetDarkMode(HWND hwnd)
{
    HMODULE hDwmapi = LoadLibrary(TEXT("dwmapi.dll"));
    if (hDwmapi) {
        PDwmSetWindowAttribute DwmSetWindowAttribute = (PDwmSetWindowAttribute)GetProcAddress(hDwmapi, "DwmSetWindowAttribute");
        if (DwmSetWindowAttribute) {
            BOOL useDarkMode = TRUE;
            DwmSetWindowAttribute(hwnd, 20, &useDarkMode, sizeof(useDarkMode));

        }
        FreeLibrary(hDwmapi);
    }
}

Window* W_Create(int width, int height)
{
    HINSTANCE hInstance = GetModuleHandle(NULL);
    int nCmdShow = SW_SHOWDEFAULT;

    WNDCLASSEX wc;
    wc.cbSize = sizeof(WNDCLASSEX);
    wc.style = CS_HREDRAW | CS_VREDRAW;
    wc.lpfnWndProc = WndProc;
    wc.cbClsExtra = 0;
    wc.cbWndExtra = 0;
    wc.hInstance = hInstance;
    wc.hIcon = LoadIcon(NULL, IDI_APPLICATION);
    wc.hIconSm = LoadIcon(NULL, IDI_APPLICATION);
    wc.hCursor = LoadCursor(NULL, IDC_ARROW);
    wc.lpszClassName = winClass;
    wc.hbrBackground = (HBRUSH)(COLOR_WINDOW+3);
    wc.lpszMenuName = NULL;

    RegisterClassEx(&wc);

    HWND winHandle = CreateWindowEx(
                                       0,
                                       winClass,
                                       "",
                                       WS_OVERLAPPEDWINDOW,
                                       CW_USEDEFAULT, CW_USEDEFAULT,
                                       width, height,
                                       NULL, NULL,
                                       hInstance,
                                       NULL
    );

    int cx = GetSystemMetrics(SM_CXSCREEN);
	int cy = GetSystemMetrics(SM_CYSCREEN);

	MoveWindow(winHandle, (cx - width)/2, (cy - height)/2, width, height, TRUE);

	if(IsDarkThemeByColor())
    {
        SetDarkMode(winHandle);
    }

	ShowWindow(winHandle, nCmdShow);
    UpdateWindow(winHandle);

    Window* w = (Window*)malloc(sizeof(Window));
    w->x =  (cx - width)/2;
    w->y =  (cy - height)/2;
    w->width = width;
    w->height = height;
    w->title = "";
    w->hwnd = winHandle;
    w->hInstance = hInstance;
    w->show = nCmdShow;

    return w;
}

void W_Close(Window* w)
{
    UnregisterClass(winClass, w->hInstance);
    free(w);
}

void W_SetTitle(Window* w, const char* title)
{
    SetWindowTextA(w->hwnd ,title);
    w->title = title;
}

void W_SetSize(Window* w, int w_, int h_)
{
    RECT rc;
	GetWindowRect(w->hwnd, &rc);
	MoveWindow(w->hwnd, rc.left, rc.top, w_, h_, TRUE);
	w->width = w_; w->height = h_;
}

void W_SetPos(Window* w, int x, int y)
{
    MoveWindow(w->hwnd, x, y, w->width, w->height, TRUE);
    w->x = x; w->y = y;
}

void W_Update(Window* w)
{
    RECT rect;
	GetWindowRect(w->hwnd, &rect);
	w->width = rect.right - rect.left;
	w->height = rect.bottom - rect.top;

	UpdateWindow(w->hwnd);
}

int W_GetWidth(Window* w)
{
    return w->width;
}

int W_GetHeight(Window* w)
{
    return w->height;
}

HWND W_GetHandle(Window* w)
{
    return w->hwnd;
}

LRESULT CALLBACK WndProc(HWND hwnd, UINT msg, WPARAM wParam, LPARAM lParam)
{
    switch(msg)
    {
        case WM_CREATE:
		break;

        case WM_CLOSE:
            DestroyWindow(hwnd);
        break;

        case WM_DESTROY:
            PostQuitMessage(0);
        break;
        default:
            return DefWindowProc(hwnd, msg, wParam, lParam);
    }
    return 0;
}

#endif //_WIN32
