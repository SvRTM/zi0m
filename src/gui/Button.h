/*
 * Button.h
 *
 *  Created on: 2 февр. 2016 г.
 *      Author: Artem.Smirnov
 */

#ifndef GUI_BUTTON_H_
#define GUI_BUTTON_H_

#include "Widget.h"
#include "TextCharacters.h"

#include <string>
#include <functional>

class Button: public Widget, public TextCharacters
{
    public:
        explicit Button(Widget *parent);
        virtual ~Button() {}

    public:
        void setGeometry(Rect rect);
        void updateGeometry() ;

        void setText(const std::u16string text);
        void setColor(u_color color);

        void setCbPressed(const std::function<void ()> &func);
        void setCbReleased(const std::function<void ()> &func);
        void setCbMoved(const std::function<void (uint16_t x, uint16_t y)> &func);

    private:
        void event(EventType type);
        void paint(MonitorDevice *const pMonitorDevice) override;

    private:
        const uint16_t borderWidth;

        std::function<void (void)> cbPressed;
        std::function<void (void)> cbReleased;
        std::function<void (uint16_t x, uint16_t y)> cbMoved;
};

#endif /* GUI_BUTTON_H_ */
