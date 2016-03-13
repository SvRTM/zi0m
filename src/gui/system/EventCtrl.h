/*
 * EventCtrl.h
 *
 *  Created on: 11 февр. 2016 г.
 *      Author: Artem.Smirnov
 */

#ifndef SRC_GUI_SYSTEM_EVENTCTRL_H_
#define SRC_GUI_SYSTEM_EVENTCTRL_H_
#pragma once

#include "../common.h"
//#include "../Widget.h"

class Widget;
class EventCtrl
{
    public:
        EventCtrl();
        virtual ~EventCtrl();

        void process(_MSG msg, Widget *widget);
};

#endif /* SRC_GUI_SYSTEM_EVENTCTRL_H_ */
