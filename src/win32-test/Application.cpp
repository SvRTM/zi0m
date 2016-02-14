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
    //setupUi();
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
}/*
 void Application::setupUi()
 {
 Button *bt = new Button();
 bt->setGeometry(Rect(10, 10, 60, 30));
 add(bt);

 bt = new Button();
 bt->setGeometry(Rect(20, 60, 60, 30));
 add(bt);

 MainWindow *mw = new MainWindow(nullptr);
 mw->setGeometry(Rect(40, 120, 60, 30));
 add(mw);
 }
 *//*
 void Application::paint(MonitorDevice *w)
 {
 w->fillRect(Rect(0, 0, w->getWidth(), w->getHight()),
 u_color { 0x00E8F6FAU });
 }
 */
