/*
 * Widget.h
 *
 *  Created on: 25 янв. 2016 г.
 *      Author: Artem.Smirnov
 */

#ifndef GUI_WIDGET_H_
#define GUI_WIDGET_H_

#include "common.h"
#include "MonitorDevice.h"
#include "system/EventCtrl.h"

#include <vector>

class Widget
{
    public:
        Widget();
        Widget(Widget *parent);
        virtual ~Widget();

    public:
        virtual void paint(MonitorDevice *pMonitorDevice);

        // Returns current position in parent. It is either position in view or frame coordinates.
        Rect *geometry();
        void setGeometry(Rect rect);
        // Returns current position in absolute screen coordinates.
        Rect frameGeometry();

        void refresh(bool r = true)
        {
            _refresh = r;
        }

        //void event();

        bool isVisible() const;
        void setVisible(bool visible);

        void setEventType(EventType type);
        EventType eventType() const;

        void add(Widget *w);
        Widget* find(int x, int y);

    protected:
        //MonitorDevice *pMonitorDevice;
        Rect rect;
        Rect screenRect;

        bool visible;
        bool _refresh;

        EventType type;

        std::vector<Widget *> widgets;
    public:
        EventCtrl *pEventCtrl;

    private:
        Widget *parent;
};

#endif /* GUI_WIDGET_H_ */
