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

void EventCtrl::process(const _MSG msg, Widget *const widget) const
{
    Button *const btn = dynamic_cast<Button *const>(widget);
    if (btn == nullptr)
    {
        Widget *w = widget->findChild(msg.pt.x, msg.pt.y);
        if (w != nullptr)
            w->event()->process(msg, w);
        return;
    }

    switch (msg.message)
    {
        case Message::TouchDown:
            if (btn->isVisible())
                btn->pressed();
            break;
        case Message::TouchUp:
            if (btn->isVisible())
                // FIXME: when the properties button is changed by pressing the button
                btn->released();
            break;
        default:
            break;
    }
}
