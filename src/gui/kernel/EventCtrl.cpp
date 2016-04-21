/*
 * EventCtrl.cpp
 *
 *  Created on: 11 февр. 2016 г.
 *      Author: Artem.Smirnov
 */

#include "EventCtrl.h"
#include "gui/widgets/Widget.h"

namespace zi0m
{

void EventCtrl::process(const _MSG msg, Widget *const widget)
{
    switch (msg.touchEvent)
    {
        case EventType::TouchStart:
        {
            // FIXME: optimize
            Widget *currWidget = widget->findWidget(msg.pt.x, msg.pt.y);
            if (currWidget == nullptr)
                currWidget = widget;

            if (prevWidget == nullptr)
            {
                currWidget->event(EventType::TouchStart, msg.pt);
                //process
                prevWidget = currWidget;
            }
            else if (prevWidget == currWidget)
            {
                if (currWidget->screen().contains(prevWidget->screen().x, prevWidget->screen().y))
                {
                    if (isEnableTouchLeave)
                    {
                        currWidget->event(EventType::TouchEnter, msg.pt);
                        isEnableTouchLeave = false;
                    }
                    else
                        currWidget->event(EventType::TouchMove, msg.pt);
                    // process
                }
            }
            else
            {
                if (!isEnableTouchLeave && EventType::TouchLeave != prevWidget->eventType())
                {
                    prevWidget->event(EventType::TouchLeave, msg.pt);
                    isEnableTouchLeave = true;
                }
                else
                    prevWidget->event(EventType::TouchMove, msg.pt);
                // process prevWidget
            }
            break;
        }

        case EventType::TouchEnd:
        {
            // FIXME: optimize
            Widget *currWidget = widget->findWidget(msg.pt.x, msg.pt.y);
            if (currWidget == nullptr)
                currWidget = widget;

            if (prevWidget == currWidget)
                prevWidget->event(EventType::TouchEnd, msg.pt);
            //process prevWidget/currWidget
            prevWidget = nullptr;
            isEnableTouchLeave = false;
            break;
        }
        default:
            break;
    }
}

}
