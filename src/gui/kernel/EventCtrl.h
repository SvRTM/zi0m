/*
 * Copyright © 2016 Artem Smirnov
 * All right reserved.
 * Author: Artem Smirnov <msvrtm@gmail.com>
 * License: http://www.gnu.org/licenses/gpl.txt
 */

#ifndef EVENTCTRL_H_
#define EVENTCTRL_H_

#include "gui/common.h"

namespace zi0m
{
class Widget;
class EventCtrl final
{
    public:
        EventCtrl() = default;
        ~EventCtrl() = default;

    public:
        void process(const Message &msg, Widget *const widget);

    private:
        Widget *prevWidget = nullptr;
        bool isEnableTouchLeave = false;
};
}
#endif /* EVENTCTRL_H_ */
