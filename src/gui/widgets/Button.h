/*
 * Button.h
 *
 *  Created on: 2 февр. 2016 г.
 *      Author: Artem.Smirnov
 */

#ifndef BUTTON_H_
#define BUTTON_H_

#include "Widget.h"
#include "AbstractButton.h"

#include <functional>

namespace zi0m
{
class Button: public AbstractTextWidget
{
    public:
        explicit Button(Point pos, Size size, Widget *const parent);
        virtual ~Button() {}

    public:
        void setCbPressed(const std::function<void ()> &func);
        void setCbReleased(const std::function<void ()> &func);
        void setCbMoved(const std::function<void (const Point &)> &func);

    private:
        void p_setSize() override;
        void p_setFont() override {}
        void p_setText() override {}
        void p_updateAllPosition() override;

        void event(const EventType type, const Point &pos) override;
        void paint(MonitorDevice *const pMonitorDevice) override;

    private:
        static constexpr uint8_t borderWidth = 1;

        std::function<void (void)> cbPressed;
        std::function<void (void)> cbReleased;
        std::function<void (const Point &pos)> cbMoved;

        static const Rect border;
        inline const Rect &Border() const
        {
            return border;
        }
};
}
#endif /* BUTTON_H_ */
