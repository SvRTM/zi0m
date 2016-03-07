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
        Button();
        Button(Widget *parent);
        virtual ~Button();

        void setText(const std::u16string text);

        void paint(MonitorDevice *pMonitorDevice) override;
        //virtual Rect geometry() const = 0;
        //virtual void clicked() const = 0;
        void pressed();
        void released();

    private:
        uint16_t borderWidth;
        Label *label;

        std::u16string m_text;
};

#endif /* GUI_BUTTON_H_ */
