/*
 * Widget.h
 *
 *  Created on: 25 янв. 2016 г.
 *      Author: Artem.Smirnov
 */

#ifndef GUI_WIDGET_H_
#define GUI_WIDGET_H_

#include "MonitorDevice.h"
#include "system/EventCtrl.h"
#include "font/Terminus.h"
#include "common.h"

#include <vector>

class Widget
{
    public:
        Widget();
        explicit Widget(Widget *const parent);
        virtual ~Widget();

    public:
        virtual void paint(MonitorDevice *const pMonitorDevice) = 0;
        void eventPaint(MonitorDevice *const pMonitorDevice);

        const EventCtrl  *event() const
        {
            return pEventCtrl;
        }

        // Returns current position in parent. It is either position in view or frame coordinates.
        const Rect *geometry() const;
        void setGeometry(Rect rect);
        void updateGeometry();
        // Returns current position in absolute screen coordinates.
        const Rect frameGeometry();

        void refresh(bool r = true)
        {
            m_refresh = r;
        }

        bool isVisible() const;
        void setVisible(bool visible);

        void setEventType(EventType type);
        EventType eventType() const;

        void addWidget(Widget *const w) ;
        Widget *findChild(int16_t x, int16_t y) const;

    protected:
        const ONE_BIT_COLOR *font;

        Rect rect;
        Rect screenRect;

        bool visible;
        bool m_refresh;

        EventType type;

        std::vector<Widget *> widgets;

    private:
        const Widget *parent;
        const EventCtrl *pEventCtrl;
};

#endif /* GUI_WIDGET_H_ */
