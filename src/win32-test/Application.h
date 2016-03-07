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

#include <windows.h>
#undef min

class Application: public ApplicationBase
{
    public:
        Application();
        virtual ~Application();

        void mainCycle();
        void init(HWND _hWnd);
        void setMessage(_MSG msg);

    private:

};

#endif /* WIN32_TEST_APPLICATION_H_ */
