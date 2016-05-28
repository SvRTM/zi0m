/*
 * Copyright © 2016 Artem Smirnov
 * All right reserved.
 * Author: Artem Smirnov <msvrtm@gmail.com>
 * License: http://www.gnu.org/licenses/gpl.txt
 */

#ifndef ABSTRACTBUTTON_H
#define ABSTRACTBUTTON_H

#include "Widget.h"
#include "AbstractTextWidget.h"

#include <functional>

namespace zi0m
{
class AbstractButton : public AbstractTextWidget
{
    public:
        explicit AbstractButton(Point pos, Size size, Alignment align, const Rect &border,
                                Widget *const parent);
        virtual ~AbstractButton() = default;

    public:
        void setCbPressed(const std::function<void ()> &func);
        void setCbReleased(const std::function<void ()> &func);
        void setCbMoved(const std::function<void (const Point &)> &func);

    private:
        void event(const EventType type, const Point &pos) override;
        virtual void p_cbReleased() = 0;


    private:
        std::function<void (void)> cbPressed = nullptr;
        std::function<void (void)> cbReleased = nullptr;
        std::function<void (const Point &pos)> cbMoved = nullptr;
};
}
#endif // ABSTRACTBUTTON_H
