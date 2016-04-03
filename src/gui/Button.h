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

    private:
        void event(EventType type);
        void paint(MonitorDevice *const pMonitorDevice) override;

    private:
        const uint16_t borderWidth;
};

#endif /* GUI_BUTTON_H_ */
