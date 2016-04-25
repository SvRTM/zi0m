/*
 * Application.cpp
 *
 *  Created on: 27 янв. 2016 г.
 *      Author: Artem.Smirnov
 */

#include "Application.h"

#include "EmuTouch.h"
#include "EmuLcd.h"
#include "gui/widgets/Button.h"
#include "samples/MainWindow.h"

#ifdef PLATFORM_WIN32
Application::Application()
    : ApplicationBase(new MainWindow())
{
    addDevice(new EmuTouch());
}

void Application::init(HWND _hWnd)
{
    ApplicationBase::init(new EmuLcd(_hWnd));
}
#elif PLATFORM_LINUX
Application::Application(const x11 *x)
    : ApplicationBase(new MainWindow())
{
    m_pX11 = x;
    addDevice(new EmuTouch());
}

void Application::init()
{
    ApplicationBase::init(new EmuLcd(&m_pX11->param));
}
#endif

void Application::setMessage(Message msg)
{
    for (InputDevice *device : getDevices())
    {
        EmuTouch *emuTouch = dynamic_cast<EmuTouch *>(device);
        if (emuTouch == nullptr)
            continue;

        emuTouch->setMessage(msg);
        break;
    }
}
