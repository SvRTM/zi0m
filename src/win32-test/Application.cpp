/*
 * Application.cpp
 *
 *  Created on: 27 янв. 2016 г.
 *      Author: Artem.Smirnov
 */

#include "Application.h"
#include "EmuTouch.h"
#include "EmuLcd.h"
#include "../gui/Button.h"
#include "MainWindow.h"

#include <iostream>

Application::Application()
        : ApplicationBase(new MainWindow())
{
    addDevice(new EmuTouch());
}
Application::~Application()
{
}

void Application::init(HWND _hWnd)
{
    ApplicationBase::init(new EmuLcd(_hWnd));
}

void Application::mainCycle()
{
    quantum();
}
void Application::setMessage(_MSG msg)
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
