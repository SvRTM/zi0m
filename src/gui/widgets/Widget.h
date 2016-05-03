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
        explicit Widget(Point pos, Size size, Widget *const parent = nullptr,
                        const Rect &border = zeroBorder);
        virtual ~Widget();

    public:
        void eventPaint(MonitorDevice *const pMonitorDevice);
        virtual void paint(MonitorDevice *const pMonitorDevice) = 0;

        inline const Widget *parent() const
        {
            return m_parent;
        }

        void addWidget(Widget *const w);

        // Returns the current position in absolute coordinates of the screen.
        inline const Rect screen() const
        {
            return {absolutePos, m_size};
        }
        inline const Point &screenPosition() const
        {
            return absolutePos;
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

        // [client area] This property holds the geometry of the widget relative to its parent and excluding the widget frame
        inline const Rect geometry() const
        {
            return {int16_t(m_pos.x + Border().x), int16_t(m_pos.y + Border().y),
                    uint16_t(m_size.width - Border().width), uint16_t(m_size.height - Border().height)
                   };
        }
        // Returns the current position in absolute coordinates of the client area of the screen.
        inline const Rect screenClient() const
        {
            return {absoluteClientPos.x, absoluteClientPos.y, m_size.width, m_size.height};
        }

        // This property holds whether the widget is visible.
        inline bool isVisible() const
        {
            return visible;
        }
        void setVisible(bool visible);

        void setEnabled(bool enabled);

        virtual void event(const EventType type, const Point &pos) = 0;
        EventType eventType() const;

        Widget *const findWidget(const Point &pos) const;

        std::vector<Widget *> childs() const;

    protected:
        virtual const Rect &Border() const = 0;
        void updateAllPosition() override;
        void setEnabledChilds(bool enabled);

    private:
        void refreshChilds();
        inline void resetEvent()
        {
            type = EventType::None;
        }


    protected:
        static const Rect zeroBorder;

        EventType type = EventType::None;
        Point absoluteClientPos;

    private:
        Point m_pos;
        Size m_size;
        Widget *const m_parent;
        Point absolutePos;
        bool visible = true;

        std::vector<Widget *> widgets;
};
}
#endif /* WIDGETS_WIDGET_H_ */
