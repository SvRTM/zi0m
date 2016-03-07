/*
 * ApplicationBase.h
 *
 *  Created on: 8 февр. 2016 г.
 *      Author: Artem.Smirnov
 */

#ifndef SRC_GUI_APPLICATIONBASE_H_
#define SRC_GUI_APPLICATIONBASE_H_

#include "system/Signal.h"
#include "system/EventCtrl.h"

#include "Widget.h"
#include "InputDevice.h"
#include "MonitorDevice.h"

#include <vector>

class ApplicationBase
{
    public:
        ApplicationBase(Widget *mainWidget);
        virtual ~ApplicationBase();

        void init(MonitorDevice *pMonitorDevice);

        void addDevice(InputDevice *device);
        std::vector<InputDevice *> getDevices();
        void quantum();

    private:
        Widget *pMainWidget;
        EventCtrl *pEventCtrl;

        std::vector<InputDevice *> devices;
        MonitorDevice *pMonitorDevice;
};

#endif /* SRC_GUI_APPLICATIONBASE_H_ */
