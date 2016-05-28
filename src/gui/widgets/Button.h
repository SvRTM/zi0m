/*
 * Copyright © 2016 Artem Smirnov
 * All right reserved.
 * Author: Artem Smirnov <msvrtm@gmail.com>
 * License: http://www.gnu.org/licenses/gpl.txt
 */

#ifndef BUTTON_H_
#define BUTTON_H_

#include "Widget.h"
#include "AbstractButton.h"

namespace zi0m
{
class Button: public AbstractButton
{
    public:
        explicit Button(Point pos, Size size, Widget *const parent);
        virtual ~Button() = default;

    private:
        void p_setSize() override;
        void p_setFont() override {}
        void p_setText() override {}
        void p_updateAllPosition() override;
        void p_cbReleased() override {}

        void paint(MonitorDevice *const pMonitorDevice) override;

    private:
        static constexpr uint8_t borderWidth = 1;

        static const Rect border;
        inline const Rect &Border() const
        {
            return border;
        }
};
}
#endif /* BUTTON_H_ */
