/*
 * EventCtrl.h
 *
 *  Created on: 11 февр. 2016 г.
 *      Author: Artem.Smirnov
 */

#ifndef SRC_GUI_SYSTEM_EVENTCTRL_H_
#define SRC_GUI_SYSTEM_EVENTCTRL_H_

#include "gui/common.h"

class Widget;
class EventCtrl
{
    public:
        EventCtrl();
        virtual ~EventCtrl();

    public:
        void process(const _MSG msg,   Widget *const widget) const;
};

#endif /* SRC_GUI_SYSTEM_EVENTCTRL_H_ */
