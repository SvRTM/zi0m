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

        // virtual void paint(MonitorDevice *w) = 0;
        void init(MonitorDevice *pMonitorDevice);

        //void add(Widget *w);
        //Widget *find(int x, int y);

        void addDevice(InputDevice *device);
        std::vector<InputDevice *> getDevices();
        void quantum();

    private:
        Widget *pMainWidget;
        EventCtrl *pEventCtrl;
        //std::vector<Widget*> widgets;
        std::vector<InputDevice *> devices;
        MonitorDevice *pMonitorDevice;
        //bool refresh;
};

#endif /* SRC_GUI_APPLICATIONBASE_H_ */
