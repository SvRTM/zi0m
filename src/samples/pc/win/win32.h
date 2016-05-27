#ifndef SAMPLES_PC_WIN_WIN32_H_
#define SAMPLES_PC_WIN_WIN32_H_

#define WIN32_LEAN_AND_MEAN  /* speed up compilations */


#include "samples/pc/Application.h"
#include "samples/pc/SimBase.h"

#include <windows.h>
#include <tchar.h>


using namespace zi0m;

class Win32 final : public SimBase
{
    public:
        Win32();

    public:
        void exec() override;

    private:
        static LRESULT CALLBACK MainWndProc(HWND hwnd, UINT winMsg, WPARAM wParam,
                                            LPARAM lParam);
        int PASCAL WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance,
                           LPSTR lpszCmdLine, int nCmdShow);

        void onPaint(HWND hwnd);
        void onLButtonDown(HWND hwnd, bool fDoubleClick, int x, int y, UINT keyFlags);
        void onMouseMove(HWND hwnd, int x, int y, UINT keyFlags);
        void onLButtonUp(HWND hwnd, int x, int y, UINT keyFlags);
        void onCommand(HWND hwnd, int id, HWND hwndCtl, UINT codeNotify);
        void onDestroy(HWND hwnd);


    private:
        static Win32 *win32Inst;

        Application app;
        bool isBtnPressed = false;
};

#endif /* SAMPLES_PC_WIN_WIN32_H_ */
