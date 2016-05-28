/*
 * Copyright © 2016 Artem Smirnov
 * All right reserved.
 * Author: Artem Smirnov <msvrtm@gmail.com>
 * License: http://www.gnu.org/licenses/gpl.txt
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

void Application::setMessage(const Message msg)
{
    for (InputDevice *device : getDevices())
        if (TypeTag::TOUCH_DEVICE == device->typeID())
        {
            EmuTouch *emuTouch = static_cast<EmuTouch *>(device);
            emuTouch->setMessage(msg);
        }
}
