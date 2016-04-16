/*
 * Button.h
 *
 *  Created on: 2 февр. 2016 г.
 *      Author: Artem.Smirnov
 */

#ifndef BUTTON_H_
#define BUTTON_H_

#include "Widget.h"
#include "gui/text/TextCharacters.h"

#include <functional>

namespace zi0m
{
class Button: public Widget, public TextCharacters
{
    public:
        explicit Button(Point pos, Size size, Widget *const parent);
        virtual ~Button() {}

    public:
        void setSize(Size size);

        void setCbPressed(const std::function<void ()> &func);
        void setCbReleased(const std::function<void ()> &func);
        void setCbMoved(const std::function<void (uint16_t x, uint16_t y)> &func);

    private:
        void updateAllPosition() override;
        void event(EventType type) override;
        void paint(MonitorDevice *const pMonitorDevice) override;

    private:
        const uint8_t borderWidth = 1;

        std::function<void (void)> cbPressed;
        std::function<void (void)> cbReleased;
        std::function<void (uint16_t x, uint16_t y)> cbMoved;
};
}
#endif /* BUTTON_H_ */
