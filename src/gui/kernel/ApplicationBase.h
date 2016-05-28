/*
 * Copyright © 2016 Artem Smirnov
 * All right reserved.
 * Author: Artem Smirnov <msvrtm@gmail.com>
 * License: http://www.gnu.org/licenses/gpl.txt
 */

#ifndef APPLICATIONBASE_H_
#define APPLICATIONBASE_H_

#include "gui/kernel/EventCtrl.h"

#include "gui/widgets/Widget.h"
#include "gui/io/InputDevice.h"
#include "gui/io/MonitorDevice.h"

#include <vector>

namespace zi0m
{
class ApplicationBase
{
    public:
        explicit ApplicationBase(Widget *const mainWidget);
        virtual ~ApplicationBase();
    private:
        ApplicationBase(const ApplicationBase &) = delete;
        ApplicationBase &operator=(const ApplicationBase &) = delete;

    public:
        void init(MonitorDevice *const pMonitorDevice);

        void addDevice(InputDevice *const device);
        const std::vector<InputDevice *> getDevices() const;
        void quantum();
        void refreshAll();

    private:
        Widget *const pMainWidget;
        EventCtrl *pEventCtrl;

        std::vector<InputDevice *> devices;
        MonitorDevice *pMonitorDevice = nullptr;
};
}

#endif /* APPLICATIONBASE_H_ */
