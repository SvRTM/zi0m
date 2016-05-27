/*
 * ApplicationBase.cpp
 *
 *  Created on: 8 февр. 2016 г.
 *      Author: Artem.Smirnov
 */

#include "ApplicationBase.h"
#include "samples/pc/EmuTouch.h"

namespace zi0m
{

ApplicationBase::ApplicationBase(Widget *const mainWidget)
    : pMainWidget(mainWidget),
      pEventCtrl(new EventCtrl())
{
    devices.reserve(1);
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
    for (InputDevice *device : devices)
    {
        const Message msg = device->getMessage();
        if (EventType::None != msg.touchEvent)
        {
            pEventCtrl->process(msg, pMainWidget);
            break;
        }
    }

    pMainWidget->eventPaint(pMonitorDevice);
}

void ApplicationBase::refreshAll()
{
    pMainWidget->refreshAll();
}
}
