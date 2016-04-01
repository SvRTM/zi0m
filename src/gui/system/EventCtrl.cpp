/*
 * EventCtrl.cpp
 *
 *  Created on: 11 февр. 2016 г.
 *      Author: Artem.Smirnov
 */

#include "EventCtrl.h"

#include "../Widget.h"
#include "../Button.h"

EventCtrl::EventCtrl() : prevWidget(nullptr)
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

//    switch (msg.touchEvent)
//    {
//        case EventType::TouchStart:
//        {
//            Widget *const currWidget = widget->findChild(msg.pt.x, msg.pt.y);
//            if (currWidget == nullptr)
//                currWidget = widget;
//            if (prevWidget == nullptr)
//            {
//                currWidget->setEventType(EventType::TouchStart);
//                prevWidget = currWidget;
//                //process
//            }
//            else if (prevWidget == currWidget)
//            {
//                if (!currWidget->frameGeometry().contains(prevWidget->frameGeometry().x,
//                                                          prevWidget->frameGeometry().y))
//                    currWidget->setEventType(EventType::TouchMove);
//            }
//            else
//            {
//                prevWidget->setEventType(EventType::TouchLeave);
//                // process prevW
//            }
//            break;
//        }
//        case EventType::TouchEnd:
//            prevWidget->setEventType(EventType::TouchEnd);
//            //process
//            prevWidget = nullptr;
//            break;

//        default:
//            break;
//    }

    switch (msg.touchEvent)
    {
        case EventType::TouchStart:
            if (btn->isVisible())
                btn->pressed();
            break;
        case EventType::TouchEnd:
            if (btn->isVisible())
                // FIXME: when the properties button is changed by pressing the button
                btn->released();
            break;
        default:
            break;
    }
}
