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
#include "font/ifont.h"
#include "common.h"
#include "additional.h"

#include <vector>

class Widget: public virtual Additional
{
    public:
        explicit Widget(Widget *const parent = nullptr);
        virtual ~Widget();

    public:
        virtual void paint(MonitorDevice *const pMonitorDevice) = 0;
        void eventPaint(MonitorDevice *const pMonitorDevice);

        inline const EventCtrl  *event() const
        {
            return pEventCtrl;
        }

        // Returns current position in parent. It is either position in view or frame coordinates.
        inline const Rect &geometry() const
        {
            return rect;
        }
        void setGeometry(Rect rect);
        // Returns current position in absolute screen coordinates.
        const Rect &screen() const
        {
            return screenRect;
        }

        inline bool isEnabled() const
        {
            return enabled;
        }
        void setEnabled(bool enable);

        void setVisible(bool visible);

        void setEventType(EventType type);
        EventType eventType() const;

        Widget *findChild(int16_t x, int16_t y) const;

    protected:
        void addWidget(Widget *const w);
        void updateGeometry();
        inline void refresh(bool refresh = true)
        {
            m_refresh = refresh;
        }


    private:
        // Returns current position in absolute screen coordinates.
        const Rect frameGeometry();

    private:
        Widget *const parent;
        const EventCtrl *pEventCtrl;


    private:
        EventType type;

        Rect rect;
        Rect screenRect;

        bool enabled;

        bool m_refresh;

        std::vector<Widget *> widgets;
};

#endif /* GUI_WIDGET_H_ */
