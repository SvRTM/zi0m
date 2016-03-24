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
#include "gui/system/singleton.h"
#include "common.h"

#include <vector>

class Widget
{
    public:
        explicit Widget(Widget *const _parent = nullptr);
        virtual ~Widget();

    public:
        virtual void paint(MonitorDevice *const pMonitorDevice) = 0;
        void eventPaint(MonitorDevice *const pMonitorDevice);

        inline const EventCtrl  *event() const
        {
            return pEventCtrl;
        }

        // Returns current position in parent. It is either position in view or frame coordinates.
        inline const Rect *geometry() const
        {
            return &rect;
        }
        void setGeometry(Rect rect);
        // Returns current position in absolute screen coordinates.
        const Rect frameGeometry();

        inline const IFont  &font() const
        {
            return *m_font;
        }
        void setFont(const IFont &font);

        inline const u_color background() const
        {
            return m_bg;
        }
        void setBackground(const u_color bg);

        void refresh(bool r = true)
        {
            m_refresh = r;
        }

        inline bool isVisible() const
        {
            return visible;
        }
        void setVisible(bool visible);

        void setEventType(EventType type);
        EventType eventType() const;

        void addWidget(Widget *const w) ;
        Widget *findChild(int16_t x, int16_t y) const;

    protected:
        void updateGeometry();

    private:
        const Widget *parent;
        const EventCtrl *pEventCtrl;
        const IFont *m_font;

        u_color m_bg;

    protected:
        EventType type;

        Rect rect;
        Rect screenRect;

        bool visible;
        bool m_refresh;

        std::vector<Widget *> widgets;
};

#endif /* GUI_WIDGET_H_ */
