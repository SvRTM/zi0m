/*
 * ApplicationBase.cpp
 *
 *  Created on: 8 февр. 2016 г.
 *      Author: Artem.Smirnov
 */

#include "ApplicationBase.h"
#include "../win32-test/EmuTouch.h"

ApplicationBase::ApplicationBase(Widget *mainWidget)
        : pMainWidget(mainWidget), pMonitorDevice(nullptr) //, refresh(true)
{
    pEventCtrl = new EventCtrl();
}

ApplicationBase::~ApplicationBase()
{
    delete pMainWidget;
    for (InputDevice *device : devices)
        delete device;
    delete pEventCtrl;
}

void ApplicationBase::init(MonitorDevice *pMonitorDevice)
{
    this->pMonitorDevice = pMonitorDevice;
}
/*
 void ApplicationBase::add(Widget *w)
 {
 widgets.push_back(w);
 }

 Widget *ApplicationBase::find(int x, int y)
 {
 for (Widget *w : widgets)
 {
 if (w->geometry()->contains(x, y))
 return w;
 }
 return nullptr;
 }
 */
void ApplicationBase::addDevice(InputDevice *device)
{
    devices.push_back(device);
}

std::vector<InputDevice *> ApplicationBase::getDevices()
{
    return devices;
}

void ApplicationBase::quantum()
{
    _MSG msg;
    for (InputDevice *device : devices)
    {
        msg = device->getMessage();
        if (Message::None != msg.message)
            break;
    }
    pEventCtrl->process(msg, pMainWidget);
    pMainWidget->paint(pMonitorDevice);
    /*
     Widget *w = find(msg.pt.x, msg.pt.y);
     if (w != nullptr)
     pEventCtrl->process(msg, w);

     if (refresh)
     {
     paint(pMonitorDevice);
     refresh = false;
     }
     for (Widget *w : widgets)
     {
     w->paint(pMonitorDevice);
     }
     */
}
