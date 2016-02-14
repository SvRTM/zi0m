/*
 * EventCtrl.cpp
 *
 *  Created on: 11 февр. 2016 г.
 *      Author: Artem.Smirnov
 */

#include "EventCtrl.h"

#include "../Widget.h"
#include "../Button.h"

EventCtrl::EventCtrl()
{
}
EventCtrl::~EventCtrl()
{
}

void EventCtrl::process(_MSG msg, Widget *widget)
{
    Button *btn = dynamic_cast<Button *>(widget);
    if (btn == nullptr)
    {
        Widget *w = widget->find(msg.pt.x, msg.pt.y);
        if (w != nullptr)
            w->pEventCtrl->process(msg, w);
        return;
    }
    switch (msg.message)
    {
        case Message::TouchDown:
            btn->pressed();
            break;
        case Message::TouchUp:
            btn->released();
            break;
        default:
            break;
    }
}
