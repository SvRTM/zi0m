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
        virtual ~Button();

        void setGeometry(Rect rect);
        void setText(const std::u16string text);

        void setColor(u_color color);

        void paint(MonitorDevice *const pMonitorDevice) override;

        void pressed() ;
        void released();

    private:
        const uint16_t borderWidth;
};

#endif /* GUI_BUTTON_H_ */
