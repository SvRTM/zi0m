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
        explicit Button(Widget *parent);
        virtual ~Button();

        void setGeometry(Rect rect);
        void setText(const std::u16string text);

        void paint(MonitorDevice *const pMonitorDevice) override;

        //virtual void clicked() const = 0;
        void pressed() ;
        void released();

    private:
        const uint16_t borderWidth;
        Label *label;
};

#endif /* GUI_BUTTON_H_ */
