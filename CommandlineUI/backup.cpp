#include "framework.h"
#include "UIMain.h"
#pragma comment(linker,"/manifestdependency:\"type='win32' name='Microsoft.Windows.Common-Controls' version='6.0.0.0' processorArchitecture='x86' publicKeyToken='6595b64144ccf1df' language='*'\"")
#define IDC_FILTER_STATIC 1001
#define IDC_2 1002
HINSTANCE g_hInstance;

LRESULT CALLBACK WindowProc(HWND hwnd, UINT uMsg, WPARAM wParam, LPARAM lParam);

int APIENTRY WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nCmdShow)
{
    // TODO: Place code here.
    g_hInstance = hInstance;
    TCHAR className[] = TEXT("my class");
    WNDCLASS wndclass = { 0 };
    wndclass.hInstance = hInstance;
    wndclass.hbrBackground = (CreateSolidBrush(RGB(30, 30, 30)));
    wndclass.lpszClassName = className;
    wndclass.lpfnWndProc = WindowProc;
    wndclass.hIcon = LoadIcon(NULL, MAKEINTRESOURCE(IDI_SMALL));

    RegisterClass(&wndclass);

    HWND hMain = CreateWindow(className, "FrameworkUI", WS_OVERLAPPEDWINDOW, 300, 300, 400, 300, NULL, NULL, hInstance, NULL);

    if (!hMain)
    {
        OutputDebugString("=),");
        return 0;
    }

    ShowWindow(hMain, SW_SHOW);

    MSG msg;
    BOOL ret;
    while (ret = GetMessage(&msg, NULL, 0, 0))
    {
        TranslateMessage(&msg);
        DispatchMessage(&msg);
    }

    return 0;
}

//                                                                                                                                                PROC
LRESULT CALLBACK WindowProc(HWND hwnd, UINT uMsg, WPARAM wParam, LPARAM lParam)
{
    static HFONT hFont;//定义静态字体变量
    switch (uMsg)
    {
    case WM_CREATE:
    {
        hFont = CreateFont(25, 6, 0, 0, 0, FALSE, FALSE, 0, DEFAULT_CHARSET, OUT_DEFAULT_PRECIS, CLIP_DEFAULT_PRECIS, DEFAULT_QUALITY, DEFAULT_PITCH | FF_SWISS, "Minecraft");//创建字体
        HWND txt1 = CreateWindow("STATIC", "Hello Minecraft", WS_CHILD | WS_VISIBLE, 10, 10, 100, 125, hwnd, (HMENU)IDC_2, g_hInstance, NULL);//创建静态文本
        SendMessage(txt1, WM_SETFONT, (WPARAM)hFont, TRUE);//发送设置字体消息
        hFont = CreateFont(15, 9, 0, 0, 0, FALSE, FALSE, 0, DEFAULT_CHARSET, OUT_DEFAULT_PRECIS, CLIP_DEFAULT_PRECIS, DEFAULT_QUALITY, DEFAULT_PITCH | FF_SWISS, "Minecraft");//创建字体
        HWND hStatic = CreateWindow("STATIC", "HAPPY\n\n BIRTHDAY\n MINECRAFT", WS_CHILD | WS_VISIBLE, 90, 70, 100, 125, hwnd, (HMENU)IDC_FILTER_STATIC, g_hInstance, NULL);//创建静态文本
        SendMessage(hStatic, WM_SETFONT, (WPARAM)hFont, TRUE);//发送设置字体消息
        hFont = CreateFont(15, 8, 0, 0, 0, FALSE, FALSE, 0, DEFAULT_CHARSET, OUT_DEFAULT_PRECIS, CLIP_DEFAULT_PRECIS, DEFAULT_QUALITY, DEFAULT_PITCH | FF_SWISS, "FZXS12");//创建字体
        HWND txt2 = CreateWindow("STATIC", "████\n█\n█\n█", WS_CHILD | WS_VISIBLE, 80, 170, 100, 125, hwnd, (HMENU)TXT_2, g_hInstance, NULL);//创建静态文本//this
        SendMessage(txt2, WM_SETFONT, (WPARAM)hFont, TRUE);//发送设置字体消息
        hFont = CreateFont(15, 8, 0, 0, 0, FALSE, FALSE, 0, DEFAULT_CHARSET, OUT_DEFAULT_PRECIS, CLIP_DEFAULT_PRECIS, DEFAULT_QUALITY, DEFAULT_PITCH | FF_SWISS, "FZXS12");//创建字体
        HWND txt3 = CreateWindow("STATIC", "█\n█\n█\n█", WS_CHILD | WS_VISIBLE, 120, 170, 100, 125, hwnd, (HMENU)TXT_3, g_hInstance, NULL);//创建静态文本//this
        SendMessage(txt3, WM_SETFONT, (WPARAM)hFont, TRUE);//发送设置字体消息
        hFont = CreateFont(15, 8, 0, 0, 0, FALSE, FALSE, 0, DEFAULT_CHARSET, OUT_DEFAULT_PRECIS, CLIP_DEFAULT_PRECIS, DEFAULT_QUALITY, DEFAULT_PITCH | FF_SWISS, "FZXS12");//创建字体
        HWND txt4 = CreateWindow("STATIC", "████\n█\n█\n█", WS_CHILD | WS_VISIBLE, 40, 170, 100, 125, hwnd, (HMENU)TXT_4, g_hInstance, NULL);//创建静态文本//this
        SendMessage(txt4, WM_SETFONT, (WPARAM)hFont, TRUE);//发送设置字体消息
        hFont = CreateFont(15, 8, 0, 0, 0, FALSE, FALSE, 0, DEFAULT_CHARSET, OUT_DEFAULT_PRECIS, CLIP_DEFAULT_PRECIS, DEFAULT_QUALITY, DEFAULT_PITCH | FF_SWISS, "FZXS12");//创建字体
        HWND txt5 = CreateWindow("STATIC", "████\n█\n█\n████", WS_CHILD | WS_VISIBLE, 160, 170, 100, 125, hwnd, (HMENU)TXT_5, g_hInstance, NULL);//创建静态文本//this
        SendMessage(txt5, WM_SETFONT, (WPARAM)hFont, TRUE);//发送设置字体消息
        break;
    }

    case WM_CTLCOLORSTATIC://拦截WM_CTLCOLORSTATIC消息
    {

        if ((HWND)lParam == GetDlgItem(hwnd, IDC_2))//2
        {
            SetTextColor((HDC)wParam, RGB(165, 120, 120));
            SetBkMode((HDC)wParam, TRANSPARENT);
        }
        if ((HWND)lParam == GetDlgItem(hwnd, IDC_FILTER_STATIC))//获得指定标签句柄用来对比
        {
            SetTextColor((HDC)wParam, RGB(65, 110, 120));//设置文本颜色
            SetBkMode((HDC)wParam, TRANSPARENT);//设置背景透明
        }
        if ((HWND)lParam == GetDlgItem(hwnd, TXT_2))//3
        {
            SetTextColor((HDC)wParam, RGB(0, 110, 20));//设置文本颜色
            SetBkMode((HDC)wParam, TRANSPARENT);//设置背景透明
        }
        if ((HWND)lParam == GetDlgItem(hwnd, TXT_3))//3
        {
            SetTextColor((HDC)wParam, RGB(0, 110, 20));//设置文本颜色
            SetBkMode((HDC)wParam, TRANSPARENT);//设置背景透明
        }
        if ((HWND)lParam == GetDlgItem(hwnd, TXT_4))//3
        {
            SetTextColor((HDC)wParam, RGB(0, 110, 20));//设置文本颜色
            SetBkMode((HDC)wParam, TRANSPARENT);//设置背景透明
        }
        if ((HWND)lParam == GetDlgItem(hwnd, TXT_5))//3
        {
            SetTextColor((HDC)wParam, RGB(0, 110, 20));//设置文本颜色
            SetBkMode((HDC)wParam, TRANSPARENT);//设置背景透明
        }
        return (INT_PTR)GetStockObject((NULL_BRUSH));//返回一个空画刷(必须)
    }
    case WM_DESTROY:
    {
        DeleteObject(hFont);//删除所创建字体对象
        PostQuitMessage(0);
        break;
    }
    }

    return DefWindowProc(hwnd, uMsg, wParam, lParam);
}

