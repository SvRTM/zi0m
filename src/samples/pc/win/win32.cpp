/*
 * Copyright © 2016 Artem Smirnov
 * All right reserved.
 * Author: Artem Smirnov <msvrtm@gmail.com>
 * License: http://www.gnu.org/licenses/gpl.txt
 */

#include "win32.h"
#include <iostream>


Win32 *Win32::win32Inst = nullptr;

Win32::Win32()
{
    win32Inst = this;
}

void Win32::exec()
{
    WinMain(GetModuleHandle(nullptr), nullptr, nullptr, SW_SHOW);
}

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
int PASCAL Win32::WinMain(HINSTANCE hInstance, HINSTANCE , LPSTR , int nCmdShow)
{
    WNDCLASS wc;
    /* Register the main window class */
    wc.style = CS_OWNDC | CS_VREDRAW | CS_HREDRAW;
    wc.lpfnWndProc = &MainWndProc;
    wc.cbClsExtra = 0;
    wc.cbWndExtra = 0;
    wc.hInstance = hInstance;
    wc.hIcon = nullptr;
    wc.hCursor = LoadCursor(nullptr, IDC_ARROW);
    wc.hbrBackground = HBRUSH(COLOR_WINDOW + 1);
    wc.lpszMenuName = nullptr;
    wc.lpszClassName = _T("zi0mClass");
    if (!RegisterClass(&wc))
    {
        Panic("Error register class");
        return 1;
    }

    /* Create the main window */
    HWND hwnd = CreateWindow(_T("zi0mClass"),
                             _T("zi0m"),
                             WS_CAPTION | WS_POPUPWINDOW | WS_MINIMIZEBOX,
                             0, 0, 320, 240,
                             nullptr,
                             nullptr,
                             hInstance,
                             nullptr
                            );
    if (!hwnd)
    {
        Panic("Error: CreateWindow");
        return 1;
    }

    RECT rect = {0, 0, 320, 240};
    AdjustWindowRect(&rect, GetWindowLong(hwnd, GWL_STYLE), false);
    int width = rect.right - rect.left;
    int height = rect.bottom - rect.top;
    GetWindowRect(hwnd, &rect);
    int xPos = (GetSystemMetrics(SM_CXSCREEN) - rect.right) / 2;
    int yPos = (GetSystemMetrics(SM_CYSCREEN) - rect.bottom) / 2;
    SetWindowPos(hwnd, nullptr, xPos, yPos, width, height, SWP_NOZORDER);


    /*##########################*/
    win32Inst->app.init(hwnd);
    /*##########################*/

    /* Show and paint the main window */
    ShowWindow(hwnd, nCmdShow);
    UpdateWindow(hwnd);

    MSG msg;
    /* Pump messages until we are done */
#if 0
    /* "Politically correct" code -- SEE MICROSOFT DOCUMENTATION */
    for (;;)
    {
        BOOL fRet = GetMessage(&msg, nullptr, 0, 0);
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
    while (GetMessage(&msg, nullptr, 0, 0))
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
LRESULT CALLBACK Win32::MainWndProc(HWND hwnd, UINT winMsg, WPARAM wParam,
                                    LPARAM lParam)
{
    switch (winMsg)
    {
        case WM_PAINT:
            win32Inst->onPaint(hwnd);
            break;

        case WM_MOUSEMOVE:
            win32Inst->onMouseMove(hwnd, (int)(short)LOWORD(lParam),
                                   (int)(short)HIWORD(lParam), (UINT)(wParam));
            break;
        case WM_LBUTTONDOWN:
            win32Inst->onLButtonDown(hwnd, false, (int)(short)LOWORD(lParam),
                                     (int)(short)HIWORD(lParam), (UINT)(wParam));
            break;
        case WM_LBUTTONUP:
            win32Inst->onLButtonUp(hwnd, (int)(short)LOWORD(lParam),
                                   (int)(short)HIWORD(lParam), (UINT)wParam);
            break;

        case WM_COMMAND:
            win32Inst->onCommand(hwnd, (int)(LOWORD(wParam)), (HWND)(lParam),
                                 (UINT)HIWORD(wParam));
            break;
        case WM_DESTROY:
            win32Inst->onDestroy(hwnd);
            break;

        /* TODO: enter more messages here */
        default:
            return DefWindowProc(hwnd, winMsg, wParam, lParam);
    }

    win32Inst->app.setMessage(win32Inst->msg);
    win32Inst->app.quantum();
    win32Inst->clearMessage();

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
void Win32::onPaint(HWND hwnd)
{
    PAINTSTRUCT ps;
    BeginPaint(hwnd, &ps);
    EndPaint(hwnd, &ps);

    app.refreshAll();
}

void Win32::onLButtonDown(HWND , bool , int x, int y, UINT )
{
    isBtnPressed = true;

    std::cout << "Touch start     : [" << x << ',' << y << ']' << std::endl;

    msg.touchEvent = EventType::TouchStart;
    msg.pt = {int16_t(x), int16_t(y)};
}

void Win32::onMouseMove(HWND , int x, int y, UINT )
{
    if (!isBtnPressed)
        return;

    std::cout << "  Touch move    : [" << x << ',' << y << ']' << std::endl;

    msg.touchEvent = EventType::TouchStart;
    msg.pt = {int16_t(x), int16_t(y)};
}

void Win32::onLButtonUp(HWND , int x, int y, UINT )
{
    isBtnPressed = false;

    std::cout << "Touch end       : [" << x << ',' << y << ']' << std::endl << std::endl;

    msg.touchEvent = EventType::TouchEnd;
    msg.pt = {int16_t(x), int16_t(y)};
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
void Win32::onCommand(HWND , int , HWND , UINT )
{
    //    switch (id)
    //    {
    //        //case IDM_ABOUT:
    //        ;
    //        /* TODO: Enter more commands here */
    //    }
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
void Win32::onDestroy(HWND )
{
    PostQuitMessage(0);
}
