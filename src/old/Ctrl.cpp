/*
 * Ctrl.cpp
 *
 *  Created on: 25 янв. 2016 г.
 *      Author: Artem.Smirnov
 */

#include "Ctrl.h"
#include "../win32-test/Application.h"

Ctrl::Ctrl(Application *app)
{
    pApp = app;
    //callback = std::bind(&Application::messageProcedure, app,
    //std::placeholders::_1);
}

Ctrl::~Ctrl()
{
    for (InputDevice *device : devices)
        delete device;
}

void Ctrl::addDevice(InputDevice *device)
{
    devices.push_back(device);
}

std::vector<InputDevice *> Ctrl::getDevices()
{
    return devices;
}

void Ctrl::quantum()
{
    for (InputDevice *device : devices)
    {
        _MSG msg = device->getMessage();
        if (Message::None == msg.message)
            continue;
        callback(msg);
    }
}

void Ctrl::paint()
{
    // pApp->pMainWindow->paint();
}
