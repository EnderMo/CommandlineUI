// FrameworkUI.cpp : 定义应用程序的入口点。
//
#include "UIMain.h"
#include "framework.h"
#include "FrameworkUI.h"
#pragma comment(linker,"/manifestdependency:\"type='win32' name='Microsoft.Windows.Common-Controls' version='6.0.0.0' processorArchitecture='x86' publicKeyToken='6595b64144ccf1df' language='*'\"")
#pragma comment(lib, "rpcrt4.lib") 
#pragma comment(lib, "COMCTL32.LIB")
#include <windows.h>
#include <iostream>
#include <stdio.h>
#include <stdlib.h>

#define IDC_2 1002
#define IDC_3 2002

#pragma warning(disable:4996);

HINSTANCE g_hInstance;
 
LRESULT CALLBACK WindowProc(HWND hwnd, UINT uMsg, WPARAM wParam, LPARAM lParam);
LRESULT CALLBACK BtnProc2(HWND, UINT, WPARAM, LPARAM);//按钮2窗口过程，但是我想把它变成输入框
LRESULT CALLBACK BtnProc3(HWND, UINT, WPARAM, LPARAM);//send按钮3窗口过程，按下后检测用户输入执行对应消息处理
 
int APIENTRY WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nCmdShow)
{
    // TODO: 在此处放置您的代码.
    g_hInstance = hInstance;
    TCHAR className[] = TEXT("my class");
    TCHAR szBtnName2[] = TEXT("MyBtn2");
    TCHAR szBtnName3[] = TEXT("MyBtn3");
    WNDCLASS wndclass = { 0 };
    wndclass.hInstance = hInstance;
    wndclass.hbrBackground = (CreateSolidBrush(RGB(30,30,30)));
    wndclass.lpszClassName = className;
    wndclass.lpfnWndProc = WindowProc;
    wndclass.hIcon = LoadIcon(NULL,MAKEINTRESOURCE(IDI_SMALL));
    wndclass.hCursor = LoadCursor(NULL, (IDC_ARROW));
     
    RegisterClass(&wndclass);
     
    HWND hMain = CreateWindow(className, "CommandlineUI", WS_OVERLAPPEDWINDOW, 300, 300, 400, 300, NULL, NULL, hInstance, NULL);
     
    if (!hMain)
    {
        OutputDebugString("=),");
        return 0;
    }
    
    ShowWindow(hMain, SW_SHOW);
    WNDCLASS wndbtn2 = { 0 };
    wndbtn2.cbClsExtra = 0;
    wndbtn2.cbWndExtra = 0;
    wndbtn2.hbrBackground = CreateSolidBrush(RGB(104, 104, 104));
    wndbtn2.hCursor = NULL;
    wndbtn2.hIcon = NULL;
    wndbtn2.hInstance = hInstance;
    wndbtn2.lpfnWndProc = BtnProc2;
    wndbtn2.lpszClassName = szBtnName2;
    wndbtn2.lpszMenuName = NULL;
    wndbtn2.style = CS_HREDRAW | CS_VREDRAW;

    if (!RegisterClass(&wndbtn2))
    {
        MessageBox(NULL, TEXT("RegisterClass wndbtn failed"), TEXT("ERROR"), 0);
        return 0;
    }
    HWND hButton2 = CreateWindow(szBtnName2, TEXT("MyButton2"),
        WS_CHILD | WS_VISIBLE, 0, 0, 0, 0, hMain, NULL, hInstance, 0);
    ShowWindow(hButton2, SW_SHOW);
    UpdateWindow(hButton2);

    //2，btn
    WNDCLASS wndbtn3 = { 0 };
    wndbtn3.cbClsExtra = 0;
    wndbtn3.cbWndExtra = 0;
    wndbtn3.hbrBackground = CreateSolidBrush(RGB(104, 104, 104));
    wndbtn3.hCursor = NULL;
    wndbtn3.hIcon = NULL;
    wndbtn3.hInstance = hInstance;
    wndbtn3.lpfnWndProc = BtnProc3;
    wndbtn3.lpszClassName = szBtnName3;
    wndbtn3.lpszMenuName = NULL;
    wndbtn3.style = CS_HREDRAW | CS_VREDRAW;

    if (!RegisterClass(&wndbtn3))
    {
        MessageBox(NULL, TEXT("RegisterClass wndbtn failed"), TEXT("ERROR"), 0);
        return 0;
    }
    HWND hButton3 = CreateWindow(szBtnName3, TEXT("MyButton3"),
        WS_CHILD | WS_VISIBLE, 0, 0, 0, 0, hMain, NULL, hInstance, 0);
    ShowWindow(hButton3, SW_SHOW);
    UpdateWindow(hButton3);
     
    MSG msg;
    BOOL ret;
    while (ret = GetMessage(&msg, NULL, 0, 0))
    {
        TranslateMessage(&msg);
        DispatchMessage(&msg);
    }
     
    return 0;
}
//自定样式声明模块
int BmpHitTest(HWND hwnd, LPARAM lParam)
{
    POINT pt;
    char txt[80];
    pt.x = LOWORD(lParam);
    pt.y = HIWORD(lParam);
    sprintf_s(txt, "x=%d;y=%d\n", LOWORD(lParam), HIWORD(lParam));
    OutputDebugString(txt);
    RECT  rc = { 375,5,390,30 };// 这是 bmp 在主窗口的位置 ！
    if (PtInRect(&rc, pt))
    {
        return IDB_BITMAP1;
    }
    return -1;
}
int MINIMIZE1(HWND hwnd, LPARAM lParam)
{
    POINT pt;
    char txt[80];
    pt.x = LOWORD(lParam);
    pt.y = HIWORD(lParam);
    sprintf_s(txt, "x=%d;y=%d\n", LOWORD(lParam), HIWORD(lParam));
    OutputDebugString(txt);
    RECT  rc = { 348,5,390,30 };// 这是 bmp 在主窗口的位置 ！
    if (PtInRect(&rc, pt))
    {
        return IDB_BITMAP2;
    }
    return -1;
}
//主窗口过程                                                                                                                                  PROC
LRESULT CALLBACK WindowProc(HWND hwnd, UINT uMsg, WPARAM wParam, LPARAM lParam)
{
    static HFONT hFont;//定义静态字体变量
    static HWND close;
    static HWND MINIMIZE;
    static HWND txt1;
    static HWND txt2;
    static HWND bt1;
    static int msLast=WM_MOUSELEAVE;
    char txt[40];
    HDC         hdc =NULL;
    HDC hdc2 = NULL;
    HDC         hdcMem;

    PAINTSTRUCT ps;
    HINSTANCE      hInstance = NULL;
    BITMAP         bitmap;

    static HBITMAP hBitmap;                  // 1 静态变量
    static HBITMAP hBitmap2;
    static HBITMAP hBitmap3;

    static int      bmWidth, bmHeight;       // 2 静态变量

 
    switch (uMsg)
    {
    case WM_CREATE:
        {
            hInstance = ((LPCREATESTRUCT)lParam)->hInstance;                 // 3
            hBitmap = LoadBitmap(hInstance, MAKEINTRESOURCE(IDB_BITMAP1));   // 4
            GetObject(hBitmap, sizeof(BITMAP), &bitmap);                    // 5
            bmWidth = bitmap.bmWidth;                                        // 6
            bmHeight = bitmap.bmHeight;
            //222222
            hInstance = ((LPCREATESTRUCT)lParam)->hInstance;                 // 3
            hBitmap2 = LoadBitmap(hInstance, MAKEINTRESOURCE(IDB_BITMAP2));   // 4
            GetObject(hBitmap, sizeof(BITMAP), &bitmap);                    // 5
            bmWidth = bitmap.bmWidth;                                        // 6
            bmHeight = bitmap.bmHeight;
            //222222
            hInstance = ((LPCREATESTRUCT)lParam)->hInstance;                 // 3
            hBitmap3 = LoadBitmap(hInstance, MAKEINTRESOURCE(IDB_BITMAP3));   // 4
            GetObject(hBitmap, sizeof(BITMAP), &bitmap);                    // 5
            bmWidth = bitmap.bmWidth;                                        // 6
            bmHeight = bitmap.bmHeight;
            //DRAW ^
            hFont = CreateFont(14, 7, 0, 0, 0, FALSE, FALSE, 0, DEFAULT_CHARSET, OUT_DEFAULT_PRECIS, CLIP_DEFAULT_PRECIS, DEFAULT_QUALITY, DEFAULT_PITCH | FF_SWISS, "Minecraft");//创建字体
            txt1 = CreateWindow("STATIC", "CommandlineUI", WS_CHILD | WS_VISIBLE | SS_NOTIFY, 10, 10, 120, 20, hwnd, (HMENU)IDC_2, g_hInstance, NULL);//创建静态文本
            SendMessage(txt1, WM_SETFONT, (WPARAM)hFont, TRUE);//发送设置字体消息
            break;
        }
    case WM_PAINT:

        hdc = BeginPaint(hwnd, &ps);                                     // 8

        hdcMem = CreateCompatibleDC(hdc);                                // 9

        SelectObject(hdcMem, hBitmap);                                   // 10

        BitBlt(hdc, 375, 5, bmWidth, bmHeight, hdcMem, 0, 0, SRCCOPY);     // 11 显示位图  

        DeleteDC(hdcMem);                                                // 12
                                   // 8

        hdcMem = CreateCompatibleDC(hdc);                                // 9

        SelectObject(hdcMem, hBitmap2);                                   // 10

        BitBlt(hdc, 347, 5, bmWidth, bmHeight, hdcMem, 0, 0, SRCCOPY);     // 11 显示位图  

        DeleteDC(hdcMem);                                                // 12

        EndPaint(hwnd, &ps);                                             // 13

        break;
    case WM_CTLCOLORSTATIC://拦截WM_CTLCOLORSTATIC消息
        {
             
            if ((HWND)lParam == GetDlgItem(hwnd, IDC_2))//2
            {
                SetTextColor((HDC)wParam, RGB(165, 120, 120));
                SetBkMode((HDC)wParam, TRANSPARENT);
            }
            if ((HWND)lParam == GetDlgItem(hwnd, IDC_CLOSE))//2
            {
                SetTextColor((HDC)wParam, RGB(199, 0, 0));
                SetBkMode((HDC)wParam, TRANSPARENT);
            }
            if ((HWND)lParam == GetDlgItem(hwnd, IDC_MINIMIZE))//2
            {
                SetTextColor((HDC)wParam, RGB(199, 0, 0));
                SetBkMode((HDC)wParam, TRANSPARENT);
            }
            return (INT_PTR)GetStockObject((NULL_BRUSH));//返回一个空画刷(必须)
        }
    case WM_SIZE:
    {
        LONG_PTR Style = ::GetWindowLongPtr(hwnd, GWL_STYLE);
        Style = Style & ~WS_CAPTION & ~WS_SYSMENU & ~WS_SIZEBOX;
        ::SetWindowLongPtr(hwnd, GWL_STYLE, Style);
        break;
    }
    case WM_LBUTTONDOWN:
    {
        if (BmpHitTest(hwnd, lParam) > 0)
        {
            DeleteObject(hBitmap);
            DeleteObject(hFont);
            PostQuitMessage(0);
            break;
        }
        if (MINIMIZE1(hwnd, lParam) > 0)
        {
            SendMessage(hwnd, WM_SYSCOMMAND, SC_MINIMIZE, 0); // 最小化
            break;
        }
        // 移动 窗口 
        SendMessage(hwnd, WM_NCLBUTTONDOWN, HTCAPTION, 0);  //向窗口发送WM_NCLBUTTONDOWN消息，HTCAPTION 标题
        break;
    }
    case WM_COMMAND:
        {
            switch (LOWORD(wParam))
            {
                case IDC_2:
                    MessageBox(hwnd, "By 末影小末EnderMo \n CopyRight 2018-2020", "COMMANDLINEUI", MB_OK | MB_ICONINFORMATION);
                break;
                case IDC_3:
                    MessageBox(hwnd, "您点击了按钮。(我需要告诉你你做了什么）", "提示", MB_OK | MB_ICONINFORMATION);
                break;
                case IDB_BITMAP1:
                {
                    case WM_DESTROY:
                    {
                    DeleteObject(hBitmap);                          // 14
                    DeleteObject(hFont);//删除所创建字体对象
                    PostQuitMessage(0);
                    break;
                    }
                }
                case IDC_MINIMIZE:
                {
                    SendMessage(hwnd, WM_SYSCOMMAND, SC_MINIMIZE, 0); // 最小化
                    break;
                }
                break;
            }
            break;
        }
    }
     
    return DefWindowProc(hwnd, uMsg, wParam, lParam);
}
//___________________________________________________________________________________________________________________________________
BOOL CALLBACK DialogProc(HWND hwndDlg, UINT uMsg, WPARAM wParam, LPARAM lParam)
{
    UNREFERENCED_PARAMETER(lParam);
    switch (uMsg)
    {
    case WM_INITDIALOG:
        SetWindowText(GetDlgItem(hwndDlg, IDC_EDIT2), (char*)lParam);
        return TRUE;
    case WM_CLOSE:
        EndDialog(hwndDlg, 0);
        return TRUE;
    case WM_COMMAND:
        if (LOWORD(wParam) == IDC_BUTTON1 || LOWORD(wParam) == IDCANCEL)
        {
            EndDialog(hwndDlg, LOWORD(wParam));
            return TRUE;
        }
        break;
    }
    return FALSE;
}
//子窗口过程---------这个按钮想做成命令输入框
LRESULT CALLBACK BtnProc2(HWND hBtn2, UINT message, WPARAM wParam, LPARAM lParam)
{
    using namespace::std;
    PAINTSTRUCT ps = { 0 };
    HDC DC = NULL;
    HDC hdc;
    switch (message)
    {
    case WM_CREATE:
    {
        MoveWindow(hBtn2, 45, 200, 250, 100, TRUE);
        //画椭圆区域，还可以画圆角，多边形等等
        HRGN hRgn = CreateRoundRectRgn(10, 10, 600, 50, 0, 10);
        SetWindowRgn(hBtn2, hRgn, TRUE);
    }
    break;
    case WM_LBUTTONDOWN: //这一段代码先不用，给一个例子，就是用户输入“gen uuid”之后按下下面“sendbtn”一段代码的按钮，执行下面的生成UUID代码
    {
        UUID uuid;
        UuidCreate(&uuid);
        unsigned char* str = (unsigned char*)malloc(256);
        UuidToStringA(&uuid, &str);
        DialogBoxParam((HINSTANCE)GetWindowLong(hBtn2, GWL_HINSTANCE),
            MAKEINTRESOURCE(IDD_DIALOG1),NULL, DialogProc, (LPARAM)(int*)str);
        RpcStringFreeA(&str);
        break;
    }
    case WM_PAINT:
    {
        DC = BeginPaint(hBtn2, &ps);
        SetBkColor(DC, RGB(104, 104, 104)); //按钮背景颜色
        SetTextColor(DC, RGB(210, 210, 210)); //按钮上的文字颜色
        TextOut(DC, 20, 19, _T("CreateUUID"), 10); //按钮上的文字
        EndPaint(hBtn2, &ps);
    }
    break;
    default:
        break;
    }
    return DefWindowProc(hBtn2, message, wParam, lParam);

}
//sendbtn-----------------------------------------------------------------------
LRESULT CALLBACK BtnProc3(HWND hBtn3, UINT message, WPARAM wParam, LPARAM lParam)
{
    using namespace::std;
    PAINTSTRUCT ps = { 0 };
    HDC DC = NULL;
    HDC hdc;
    switch (message)
    {
    case WM_CREATE:
    {
        MoveWindow(hBtn3, 295, 200, 250, 100, TRUE);
        //画椭圆区域，还可以画圆角，多边形等等
        HRGN hRgn = CreateRoundRectRgn(10, 10, 50, 50, 0, 10);
        SetWindowRgn(hBtn3, hRgn, TRUE);
    }
    break;
    case WM_LBUTTONDOWN:
    {
        //检测并处理用户输入
        return 0;
    }
    case WM_PAINT:
    {
        DC = BeginPaint(hBtn3, &ps);
        SetBkColor(DC, RGB(104, 104, 104)); //按钮背景颜色
        SetTextColor(DC, RGB(210, 210, 210)); //按钮上的文字颜色
        TextOut(DC, 20, 19, _T("->"), 2); //按钮上的文字
        EndPaint(hBtn3, &ps);
    }
    break;
    default:
        break;
    }
    return DefWindowProc(hBtn3, message, wParam, lParam);

}

