/****************************************************************************
 *                                                                          *
 * File    : main.c                                                         *
 *                                                                          *
 * Purpose : Generic Win32 application.                                     *
 *                                                                          *
 * History : Date      Reason                                               *
 *           00/00/00  Created                                              *
 *                                                                          *
 ****************************************************************************/

#ifdef WIN32

#define WIN32_LEAN_AND_MEAN  /* speed up compilations */
#include <windows.h>
#include <windowsx.h>
#include <commctrl.h>
#include <tchar.h>

#include "Application.h"

#define NELEMS(a)  (sizeof(a) / sizeof((a)[0]))

/** Prototypes **************************************************************/

static LRESULT WINAPI MainWndProc(HWND, UINT, WPARAM, LPARAM);
static void Main_OnPaint(HWND);
static void Main_OnLButtonDown(HWND, BOOL, int, int, UINT);
static void Main_OnLButtonUp(HWND, int, int, UINT);
static void Main_OnCommand(HWND, int, HWND, UINT);
static void Main_OnDestroy(HWND);

/** Global variables ********************************************************/

static HINSTANCE ghInstance;
static int mouse_x = -1;
static int mouse_y = -1;
static Application app;
static _MSG _msg;

/****************************************************************************
 *                                                                          *
 * Function: WinMain                                                        *
 *                                                                          *
 * Purpose : Initialize the application.  Register a window class,          *
 *           create and display the main window and enter the               *
 *           message loop.                                                  *
 *                                                                          *
 * History : Date      Reason                                               *
 *           00/00/00  Created                                              *
 *                                                                          *
 ****************************************************************************/
int PASCAL WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance,
                   LPSTR lpszCmdLine, int nCmdShow)
{
    //INITCOMMONCONTROLSEX icc;
    WNDCLASS wc;
    HWND hwnd;
    MSG msg;

    ghInstance = hInstance;

    /* Initialize common controls. Also needed for MANIFEST's */
    /*
     * TODO: set the ICC_???_CLASSES that you need.
     */
    //icc.dwSize = sizeof(icc);
    //icc.dwICC = ICC_WIN95_CLASSES /*|ICC_COOL_CLASSES|ICC_DATE_CLASSES|ICC_PAGESCROLLER_CLASS|ICC_USEREX_CLASSES|... */;
    //InitCommonControlsEx(&icc);
    /* Load Rich Edit control support */
    /*
     * TODO: uncomment one of the lines below, if you are using a Rich Edit control.
     */
    // LoadLibrary(_T("riched32.dll"));  // Rich Edit v1.0
    // LoadLibrary(_T("riched20.dll"));  // Rich Edit v2.0, v3.0
    /*
     * TODO: uncomment line below, if you are using the Network Address control (Windows Vista+).
     */
    // InitNetworkAddressControl();
    /* Register the main window class */
    wc.lpszClassName = _T("zi0mClass");
    wc.lpfnWndProc = MainWndProc;
    wc.style = CS_OWNDC | CS_VREDRAW | CS_HREDRAW;
    wc.hInstance = ghInstance;
    //wc.hIcon = LoadIcon(ghInstance, MAKEINTRESOURCE(IDR_ICO_MAIN));
    wc.hCursor = LoadCursor(NULL, IDC_ARROW);
    wc.hbrBackground = (HBRUSH) (COLOR_WINDOW + 1);
    //wc.lpszMenuName = MAKEINTRESOURCE(IDR_MNU_MAIN);
    wc.cbClsExtra = 0;
    wc.cbWndExtra = 0;
    if (!RegisterClass(&wc))
        return 1;

    /* Create the main window */
    hwnd = CreateWindow(_T("zi0mClass"),
                        _T("zi0m"),
                        WS_OVERLAPPEDWINDOW,    //|WS_HSCROLL|WS_VSCROLL,
                        CW_USEDEFAULT,
                        CW_USEDEFAULT,
                        320,
                        240,
                        NULL,
                        NULL,
                        ghInstance,
                        NULL
                       );
    if (!hwnd)
        return 1;
    app.init(hwnd);

    /* Show and paint the main window */
    ShowWindow(hwnd, nCmdShow);
    UpdateWindow(hwnd);

    /* Pump messages until we are done */
#if 0
    /* "Politically correct" code -- SEE MICROSOFT DOCUMENTATION */
    for (;;)
    {
        BOOL fRet = GetMessage(&msg, NULL, 0, 0);
        if (fRet == -1) /* Error */
        {
            /* TODO: handle the error from GetMessage() */
            //__debugbreak();
            __builtin_trap();
            return -1;
        }
        else if (fRet == 0) /* WM_QUIT */
            break;
        else /* Not error or WM_QUIT */
        {
            TranslateMessage(&msg);
            DispatchMessage(&msg);
        }
    }
#else
    /* "Commonly seen" code */
    while (GetMessage(&msg, NULL, 0, 0))
    {
        TranslateMessage(&msg);
        DispatchMessage(&msg);
    }
#endif

    return msg.wParam;
}

/****************************************************************************
 *                                                                          *
 * Function: MainWndProc                                                    *
 *                                                                          *
 * Purpose : Process application messages.                                  *
 *                                                                          *
 * History : Date      Reason                                               *
 *           00/00/00  Created                                              *
 *                                                                          *
 ****************************************************************************/

static LRESULT CALLBACK MainWndProc(HWND hwnd, UINT msg, WPARAM wParam,
                                    LPARAM lParam)
{
    switch (msg)
    {
        case WM_PAINT:
            Main_OnPaint(hwnd);
            //HANDLE_MSG(hwnd, WM_PAINT, Main_OnPaint);
            break;
        case WM_LBUTTONDOWN:
            Main_OnLButtonDown(hwnd, false, (int) (short) (LOWORD(lParam)),
                               (int) (short) (HIWORD(lParam)), (UINT) (wParam));
            //HANDLE_MSG(hwnd, WM_LBUTTONDOWN, Main_OnLButtonDown);
            break;
        case WM_LBUTTONUP:
            Main_OnLButtonUp(hwnd, (int) (short) (LOWORD(lParam)),
                             (int) (short) (HIWORD(lParam)), (UINT) wParam);
            //HANDLE_MSG(hwnd, WM_LBUTTONUP, Main_OnLButtonUp);
            break;
            HANDLE_MSG(hwnd, WM_COMMAND, Main_OnCommand)
            ;
            HANDLE_MSG(hwnd, WM_DESTROY, Main_OnDestroy);
        /* TODO: enter more messages here */
        default:
            return DefWindowProc(hwnd, msg, wParam, lParam);
    }
    app.setMessage(_msg);
    app.mainCycle();

    _msg.pt.x = -1;
    _msg.pt.y = -1;
    _msg.message = Message::None;
    app.setMessage(_msg);

    return 0L;
}

/****************************************************************************
 *                                                                          *
 * Function: Main_OnPaint                                                   *
 *                                                                          *
 * Purpose : Process a WM_PAINT message.                                    *
 *                                                                          *
 * History : Date      Reason                                               *
 *           00/00/00  Created                                              *
 *                                                                          *
 ****************************************************************************/

static void Main_OnPaint(HWND hwnd)
{
    PAINTSTRUCT ps;
    RECT rc;

    BeginPaint(hwnd, &ps);
    GetClientRect(hwnd, &rc);
    DrawText(ps.hdc, _T("Hello, Windows!"), -1, &rc,
             DT_SINGLELINE | DT_CENTER | DT_VCENTER);
    EndPaint(hwnd, &ps);
}

static void Main_OnLButtonDown(HWND hwnd, BOOL fDoubleClick, int x, int y,
                               UINT keyFlags)
{
    _msg.pt.x = x;
    _msg.pt.y = y;
    _msg.message = Message::TouchDown;

    mouse_x = x;
    mouse_y = y;
}

static void Main_OnLButtonUp(HWND hwnd, int x, int y, UINT keyFlags)
{
    _msg.pt.x = x;
    _msg.pt.y = y;
    _msg.message = Message::TouchUp;

    mouse_x = -1;
    mouse_y = -1;
}

/****************************************************************************
 *                                                                          *
 * Function: Main_OnCommand                                                 *
 *                                                                          *
 * Purpose : Process a WM_COMMAND message.                                  *
 *                                                                          *
 * History : Date      Reason                                               *
 *           00/00/00  Created                                              *
 *                                                                          *
 ****************************************************************************/

static void Main_OnCommand(HWND hwnd, int id, HWND hwndCtl, UINT codeNotify)
{
    switch (id)
    {
            //case IDM_ABOUT:
            ;
            /* TODO: Enter more commands here */
    }
}

/****************************************************************************
 *                                                                          *
 * Function: Main_OnDestroy                                                 *
 *                                                                          *
 * Purpose : Process a WM_DESTROY message.                                  *
 *                                                                          *
 * History : Date      Reason                                               *
 *           00/00/00  Created                                              *
 *                                                                          *
 ****************************************************************************/

static void Main_OnDestroy(HWND hwnd)
{
    PostQuitMessage(0);
}

void init_for_win32()
{
    WinMain(GetModuleHandle(NULL), NULL, NULL, SW_SHOW);
}

#endif
