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
HWND c_hwnd;
 
LRESULT CALLBACK WindowProc(HWND hwnd, UINT uMsg, WPARAM wParam, LPARAM lParam);
LRESULT CALLBACK BtnProc2(HWND, UINT, WPARAM, LPARAM);//按钮2
LRESULT CALLBACK BtnProc3(HWND, UINT, WPARAM, LPARAM);//send按钮3窗口过程，按下后检测用户输入执行对应消息处理
//------------------------------------------------------------------------------------------------------------------------
// for easy replace ，set UUUUIIDD=WWWWWWWW-XXXX-YYYY-ZZZZ-WWWWWWWWWWWW ！
// 这个函数只要运行 一次 ！
void WriteJson()
{
    FILE* fp = fopen("manifest.json", "wt");
    if (fp)
    {
        fprintf(fp,
            "{\n"
            "\"format_version\": 1,\n"
            "\"header\": {\n"
            "    \"description\": \"资源包显示的介绍（这个manifest只可以用于材质，资源音效之类的）-使用§修改文本颜色- ！-这个文件中不要包含中文！否则会出现乱码！请删除这些中文内容！-\",\n"
            "    \"name\": \"资源包展示的名称\",\n"
            "    \"uuid\": \"WWWWWWWW-XXXX-YYYY-ZZZZ-WWWWWWWWWWWW\",\n"
            "    \"version\": [0, 0, 1],\n"
            "    \"min_engine_version\": [1, 12, 0]\n"
            "},\n"
            "\"modules\": [\n"
            "    {\n"
            "        \"description\": \"resourcePack.vanilla.description\",\n"
            "        \"type\": \"resources\",\n"
            "        \"uuid\": \"53644fac-a276-42e5-843f-a3c6f169a9ab\",\n"
            "        \"version\": [0, 0, 1]\n"
            "    }\n"
            "]\n"
            "}"
        );
        fclose(fp);
    }
}
// 重写 Uuid
void SetJsonUuid(char* newJsonUuid)
{
    FILE* fp = fopen("\manifest.json", "rt");
    int len;
    char buf[1024];
    if (fp)
    {// read
        len = fread(buf, 1, sizeof(buf), fp);
        buf[len] = 0; // become string
        fclose(fp);
    }
    // 
    char* start;
    int sublen = strlen(newJsonUuid);
    start = strstr(buf, "WWWWWWWW-XXXX-YYYY-ZZZZ-WWWWWWWWWWWW");
    while (start)
    {
        memmove(start, newJsonUuid, sublen);
        start += sublen;
        start = strstr(buf, "WWWWWWWW-XXXX-YYYY-ZZZZ-WWWWWWWWWWWW");
    }
    //
    fp = fopen("\manifest.json", "wt");
    if (fp)
    {// write
        fwrite(buf, 1, len, fp);
        fclose(fp);
    }
}
//-----------------------------------------------------------------------------
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
    wndclass.hIcon = LoadIcon(g_hInstance,MAKEINTRESOURCE(IDI_SMALL));
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
    wndbtn3.hCursor = LoadCursor(g_hInstance,MAKEINTRESOURCE(IDC_CURSOR3));
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
                    MessageBox(hwnd, "By 末影小末EnderMo \n CopyRight 2018-2020\n\n输入help就可以看帮助啦QwQ", "COMMANDLINEUI", MB_OK | MB_ICONINFORMATION);
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
//________________________________________________________________________________________________UUID POP___________________________________
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
//子窗口过程---------命令输入框 ----------------------------------------------------------------
static char m_strInput[70] = "";
LRESULT CALLBACK BtnProc2(HWND hBtn2, UINT message, WPARAM wParam, LPARAM lParam)
{
    static POINT m_CaretPos;
    static int wid = 0;

    PAINTSTRUCT ps = { 0 };
    HDC DC = NULL;
    //    RECT rc;
    //    char prompt[40];
    switch (message)
    {
    case WM_CREATE:
    {
        MoveWindow(hBtn2, 50, 210, 250, 39, TRUE);
        //
        SetFocus(hBtn2);
        ::CreateCaret(hBtn2, NULL, 1, 18);
        m_CaretPos.x = 2;// 1 pxl bigger
        m_CaretPos.y = 2;
        ::SetCaretPos(m_CaretPos.x, m_CaretPos.y);
        ShowCaret(hBtn2);
        //画椭圆区域，还可以画圆角，多边形等等
 //       HRGN hRgn = CreateRoundRectRgn(10, 10, 600, 50, 0, 10);
//        SetWindowRgn(hBtn2, hRgn, TRUE);
    }
    break;
    case WM_LBUTTONDOWN:
    {
        //
        SetFocus(hBtn2);
        ::CreateCaret(hBtn2, NULL, 1, 18);
        ShowCaret(hBtn2);
        break;
    }
    case WM_PAINT:
    {
        DC = BeginPaint(hBtn2, &ps);
        SetBkColor(DC, RGB(104, 104, 104));
        SetTextColor(DC, RGB(67, 166, 66));
        TextOut(DC, 1, 2, m_strInput, strlen(m_strInput));
        //more left 1 than m_CaretPos.x=2
        EndPaint(hBtn2, &ps);
    }
    break;
    case WM_SETFOCUS:
        ShowCaret(hBtn2);
        break;
    case WM_KILLFOCUS:
        HideCaret(hBtn2);
        break;
    case WM_CHAR:
    {
        DC = GetDC(hBtn2);
        int len = strlen(m_strInput);
        if ((char)wParam == 13)
        {
            OutputDebugString("input finish !");
            return 0;
        }
        if ((char)wParam == 8) // backpace
        {
            if (len > 0)
            {
                if ((BYTE)m_strInput[len - 1] >= 0x80)
                {// CN TXT
                    GetCharWidth32(DC, 'L', 'L', &wid);// =10
                    m_strInput[len - 1] = 0;
                    len--;
                    m_strInput[len - 1] = 0;
                    m_CaretPos.x -= 2 * wid;
                }
                else
                {
                    GetCharWidth32(DC, m_strInput[len - 1], m_strInput[len - 1], &wid);
                    m_strInput[len - 1] = 0;
                    m_CaretPos.x -= wid;
                }
            }
        }
        else
        {
            if ((BYTE)wParam >= 0x80)
            {// 汉字
                GetCharWidth32(DC, 'L', 'L', &wid);// W=15 L=10
                //                sprintf(prompt,"%d\n",wid);
                //                OutputDebugString(prompt);
            }
            else
            {
                GetCharWidth32(DC, wParam, wParam, &wid);
            }
            // not strcat !
            m_strInput[len] = wParam;
            m_strInput[len + 1] = 0;
            m_CaretPos.x += wid;
        }
        SetCaretPos(m_CaretPos.x, m_CaretPos.y);
        // all !!
        InvalidateRect(hBtn2, 0, TRUE);
        break;
    }
    case WM_KEYDOWN:
    {
        switch (wParam)
        {
        case VK_LEFT:
        {
            if (m_CaretPos.x > 2)
            {
                int w = 10;
                //GetCharWidth32(DC,'L','L',&w);// W=15 L=10
                m_CaretPos.x -= w;
                SetCaretPos(m_CaretPos.x, m_CaretPos.y);
            }
            break;
        }
        case VK_RIGHT:
        {
            if (m_CaretPos.x < 200)
            {
                int w = 10;
                //GetCharWidth32(DC,'L','L',&w);// W=15 L=10
                m_CaretPos.x += w;
                SetCaretPos(m_CaretPos.x, m_CaretPos.y);
            }
            break;
        }
        }
        break;
    }
    default:
        break;
    }
    return DefWindowProc(hBtn2, message, wParam, lParam);

}
//sendbtn----------------------------------------------------------------------------------------
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
        MoveWindow(hBtn3, 300, 200, 250, 100, TRUE);
        //画椭圆区域，还可以画圆角，多边形等等
        HRGN hRgn = CreateRoundRectRgn(10, 10, 50, 50, 0, 10);
        SetWindowRgn(hBtn3, hRgn, TRUE);
    }
    break;
    case WM_LBUTTONDOWN:
    {
        //指向UUID生成---------------------------------------------------------------------------------
        if (strncmp(m_strInput, "gen uuid", 11) == 0) // same
        {
            UUID uuid;
            UuidCreate(&uuid);
            unsigned char* str = (unsigned char*)malloc(256);
            UuidToStringA(&uuid, &str);
            DialogBoxParam((HINSTANCE)GetWindowLong(hBtn3, GWL_HINSTANCE),
                MAKEINTRESOURCE(IDD_DIALOG1), NULL, DialogProc, (LPARAM)(int*)str);
            RpcStringFreeA(&str);
        }
        // CREATE uuid in txt-----------------------------------------------------------------------
        if (strncmp(m_strInput, "build uuid in txt", 14) == 0) // same
        {
            UUID uuid;
            UuidCreate(&uuid);
            UUID uuid2;
            UuidCreate(&uuid2);
            UUID uuid3;
            UuidCreate(&uuid3);
            unsigned char* str = (unsigned char*)malloc(256);
            UuidToStringA(&uuid, &str);
            unsigned char* str1 = (unsigned char*)malloc(256);
            UuidToStringA(&uuid2,  &str1);
            unsigned char* str2 = (unsigned char*)malloc(256);
            UuidToStringA(&uuid3, &str2);
            system("del uuid.txt");
            ofstream outfile;

            outfile.open("uuid.txt", ios::out | ios::app);

            outfile << (char*)str << "\n" << endl;
            outfile << (char*)str1 << "\n" << endl;
            outfile << (char*)str2 << "\n" << endl;


            outfile.close();
            RpcStringFreeA(&str);
            MessageBox(NULL, "UUID 已成功创建于uuid.txt中", "COMPLETE", 0);
            system("uuid.txt");
            return 0;
        }
        //build manifest----------------------------------------------------------------------------
        if (strncmp(m_strInput, "build manifest", 14) == 0)
        {
            UUID uuid;
            UuidCreate(&uuid);
            unsigned char* str = (unsigned char*)malloc(256);
            UuidToStringA(&uuid, &str);
            system("del manifest.json");
            //在这里打开一个manifest.json，没有则建造，存在则替换
            WriteJson();
            SetJsonUuid((char*)str);
            RpcStringFreeA(&str);
            MessageBox(NULL, "MANIFEST.JSON （用于MCBE资源包）建造完成！即将打开文件。\n\n UUID已经自动重新构建，请勿再次修改！", "manifest build", 0);
            system("start notepad.exe manifest.json");
            return 0;
        }
        ///THEME----------------------------------------------------------------------------------------
        if (strncmp(m_strInput, "settheme light", 15) == 0)
        {
            MessageBox(hBtn3, "这个命令正在开发，如果开发不成功，将在未来的版本中被移除。", "无法执行命令", 0);
        }
        //help————————————————————————————————————————————————————————————————————————————————————————————————
        if (strncmp(m_strInput, "help", 4) == 0) // same
        {
            MessageBox(hBtn3, " gen uuid -生成UUID \n\n build uuid in txt -在当前目录下将uuid写入uuid.txt \n\n build manifest -建立适用于MCPE的插件MANIFEST \n\n ", "COMMANDLINEUI", MB_OK);
        }
        //
        //            if(.........) {;}
        else
        {
            //如果不存在
            //MessageBox(NULL, "//", "//", 0);
        }
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