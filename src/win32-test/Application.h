/*
 * Application.h
 *
 *  Created on: 27 янв. 2016 г.
 *      Author: Artem.Smirnov
 */

#ifndef WIN32_TEST_APPLICATION_H_
#define WIN32_TEST_APPLICATION_H_

#include "../gui/ApplicationBase.h"
#include "MainWindow.h"
#include "config.h"

#ifdef PLATFORM_WIN32
    #include <windows.h>
    #undef min
#elif PLATFORM_LINUX
    #include "x11.h"
#endif

class Application: public ApplicationBase
{
    public:
#ifdef PLATFORM_WIN32
        Application();
#elif PLATFORM_LINUX
        Application(const x11 *x);
#endif
        virtual ~Application();

    public:
#ifdef PLATFORM_WIN32
        void init(HWND _hWnd);
#elif PLATFORM_LINUX
        void init();
#endif

        void setMessage(_MSG msg);

    private:
#if PLATFORM_LINUX
        const x11 *m_pX11;
#endif
};

#endif /* WIN32_TEST_APPLICATION_H_ */
