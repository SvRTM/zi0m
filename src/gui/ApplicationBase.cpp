/*
 * ApplicationBase.cpp
 *
 *  Created on: 8 февр. 2016 г.
 *      Author: Artem.Smirnov
 */

#include "ApplicationBase.h"
#include "../win32-test/EmuTouch.h"

ApplicationBase::ApplicationBase(Widget *mainWidget)
        : pMainWidget(mainWidget), pMonitorDevice(nullptr)
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
        if (Message::_None != msg.message)
            break;
    }
    pEventCtrl->process(msg, pMainWidget);
    pMainWidget->eventPaint(pMonitorDevice);
}
