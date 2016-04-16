/*
 * Widget.h
 *
 *  Created on: 25 янв. 2016 г.
 *      Author: Artem.Smirnov
 */

#ifndef WIDGETS_WIDGET_H_
#define WIDGETS_WIDGET_H_

#include "gui/io/MonitorDevice.h"
#include "gui/kernel/EventCtrl.h"
#include "gui/text/font/ifont.h"
#include "gui/common.h"
#include "gui/kernel/additional.h"

#include <vector>

namespace zi0m
{
class Widget : public virtual Additional
{
    public:
        explicit Widget(Point pos, Size size, Widget *const m_parent = nullptr);
        virtual ~Widget();

    public:
        void eventPaint(MonitorDevice *const pMonitorDevice);
        virtual void paint(MonitorDevice *const pMonitorDevice) = 0;

        const Widget *parent() const
        {
            return m_parent;
        }

        void addWidget(Widget *const w);

        // Returns current position in absolute screen coordinates.
        inline const Rect screen() const
        {
            return {absolutePos, m_size};
        }

        // This property holds the position of the widget within its parent widget.
        inline const Point &pos() const
        {
            return m_pos;
        }
        void setPosition(Point pos);

        // This property holds the size of the widget excluding any window frame.
        inline const Size &size() const
        {
            return m_size;
        }
        void setSize(const Size size);

        // This property holds whether the widget is visible.
        inline bool isVisible() const
        {
            return visible;
        }
        void setVisible(bool visible);

        void setEnabled(bool enabled);

        virtual void event(const EventType type) = 0;
        EventType eventType() const;

        Widget *const findWidget(int16_t x, int16_t y) const;

    protected:
        void updateAllPosition() override;

    private:
        void refreshChilds();
        void resetEvent()
        {
            type = EventType::None;
        }

    protected:
        EventType type;
        Point absolutePos;

    private:
        Point m_pos;
        Size m_size;
        Widget *const m_parent;
        bool visible = true;

        std::vector<Widget *> widgets;
};
}
#endif /* WIDGETS_WIDGET_H_ */
