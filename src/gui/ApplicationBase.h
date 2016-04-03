/*
 * ApplicationBase.h
 *
 *  Created on: 8 февр. 2016 г.
 *      Author: Artem.Smirnov
 */

#ifndef SRC_GUI_APPLICATIONBASE_H_
#define SRC_GUI_APPLICATIONBASE_H_

#include "system/EventCtrl.h"

#include "Widget.h"
#include "InputDevice.h"
#include "MonitorDevice.h"

#include <vector>

class ApplicationBase
{
    public:
        explicit ApplicationBase(Widget *const mainWidget);
        virtual ~ApplicationBase();

        void init(MonitorDevice *const pMonitorDevice);

        void addDevice(InputDevice *const device);
        const std::vector<InputDevice *> getDevices() const;
        void quantum();

    private:
        Widget *const pMainWidget;
        EventCtrl *pEventCtrl;

        std::vector<InputDevice *> devices;
        MonitorDevice *pMonitorDevice;
};

#endif /* SRC_GUI_APPLICATIONBASE_H_ */
