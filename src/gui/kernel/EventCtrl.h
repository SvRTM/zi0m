/*
 * EventCtrl.h
 *
 *  Created on: 11 февр. 2016 г.
 *      Author: Artem.Smirnov
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
        explicit EventCtrl() {}
        virtual ~EventCtrl() {}

    public:
        void process(const Message msg, Widget *const widget);

    private:
        Widget *prevWidget = nullptr;
        bool isEnableTouchLeave = false;
};
}
#endif /* EVENTCTRL_H_ */
