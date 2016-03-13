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

#ifdef WIN32
#include <windows.h>
#undef min
#elif LINUX
#include "x11.h"
#endif

class Application: public ApplicationBase
{
    public:
        Application();
        Application(const x11 *x);
        virtual ~Application();

        void mainCycle();

#ifdef WIN32
        void init(HWND _hWnd);
#elif LINUX
        void init();
#endif

        void setMessage(_MSG msg);

    private:
        const x11 *_x11;

};

#endif /* WIN32_TEST_APPLICATION_H_ */
