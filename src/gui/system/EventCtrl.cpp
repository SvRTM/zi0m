/*
 * EventCtrl.cpp
 *
 *  Created on: 11 февр. 2016 г.
 *      Author: Artem.Smirnov
 */

#include "EventCtrl.h"
#include "../Widget.h"

EventCtrl::EventCtrl() : prevWidget(nullptr), isEnableTouchLeave(false)
{
}

void EventCtrl::process(const _MSG msg, Widget *const widget)
{
    switch (msg.touchEvent)
    {
        case EventType::TouchStart:
        {
            Widget *currWidget = widget->exFindChild(msg.pt.x, msg.pt.y);
            if (currWidget == nullptr)
                currWidget = widget;

            if (prevWidget == nullptr)
            {
                currWidget->event(EventType::TouchStart);
                //process
                prevWidget = currWidget;
            }
            else if (prevWidget == currWidget)
            {
                if (!currWidget->screen().contains(prevWidget->screen().x,
                                                   prevWidget->screen().y))
                {
                    if (isEnableTouchLeave)
                        currWidget->event(EventType::TouchEnter);
                    else
                        currWidget->event(EventType::TouchMove);
                    isEnableTouchLeave = false;
                    // process
                }
            }
            else
            {
                if (!isEnableTouchLeave && EventType::TouchLeave != prevWidget->eventType())
                {
                    prevWidget->event(EventType::TouchLeave);
                    isEnableTouchLeave = true;
                }
                else
                    prevWidget->event(EventType::TouchMove);
                // process prevWidget
            }
            break;
        }

        case EventType::TouchEnd:
            prevWidget->event(EventType::TouchEnd);
            //process prevWidget/currWidget
            prevWidget = nullptr;
            isEnableTouchLeave = false;
            break;

        default:
            break;
    }
}
