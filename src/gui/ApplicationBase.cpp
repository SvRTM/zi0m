/*
 * ApplicationBase.cpp
 *
 *  Created on: 8 февр. 2016 г.
 *      Author: Artem.Smirnov
 */

#include "ApplicationBase.h"
#include "win32-test/EmuTouch.h"


ApplicationBase::ApplicationBase(Widget *const mainWidget)
    : pMainWidget(mainWidget),
      pEventCtrl(new EventCtrl()),
      pMonitorDevice(nullptr)
{
}

ApplicationBase::~ApplicationBase()
{
    if (pMainWidget)
        delete pMainWidget;
    for (InputDevice *device : devices)
        delete device;
    delete pEventCtrl;
}

void ApplicationBase::init(MonitorDevice *const pMonitorDevice)
{
    this->pMonitorDevice = pMonitorDevice;
}

void ApplicationBase::addDevice(InputDevice *const device)
{
    devices.push_back(device);
}

const std::vector<InputDevice *> ApplicationBase::getDevices() const
{
    return devices;
}

void ApplicationBase::quantum()
{
    _MSG msg;
    for (InputDevice *device : devices)
    {
        msg = device->getMessage();
        if (EventType::_None != msg.touchEvent)
            break;
    }

    if (EventType::_None != msg.touchEvent)
        pEventCtrl->process(msg, pMainWidget);

    pMainWidget->eventPaint(pMonitorDevice);
}
