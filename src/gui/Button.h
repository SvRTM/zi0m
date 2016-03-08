/*
 * Button.h
 *
 *  Created on: 2 февр. 2016 г.
 *      Author: Artem.Smirnov
 */

#ifndef GUI_BUTTON_H_
#define GUI_BUTTON_H_

#include "Widget.h"
#include "Label.h"

#include <string>

class Button: public Widget
{
    public:
        Button(Widget *parent, Alignment align = Alignment::Center);
        virtual ~Button();

        void setGeometry(Rect rect);
        void setText(const std::u16string text);

        void paint(MonitorDevice * const pMonitorDevice) override;
        //virtual Rect geometry() const = 0;
        //virtual void clicked() const = 0;
        void pressed();
        void released();

    private:
        const uint16_t borderWidth;

        Alignment align;
        Label *label;

        std::u16string m_text;

        struct {
                Rect rect;

        } sPressed;
};

#endif /* GUI_BUTTON_H_ */
