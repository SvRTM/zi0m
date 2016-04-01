/*
 * Label.h
 *
 *  Created on: 6 марта 2016 г.
 *      Author: Artem.Smirnov
 */

#ifndef SRC_GUI_LABEL_H_
#define SRC_GUI_LABEL_H_

#include "Widget.h"
#include "TextCharacters.h"

#include <string>

class Label: public Widget, protected TextCharacters
{
    public:
        explicit Label(Widget *parent,
                       Alignment align = (Alignment) (Alignment::VCenter | Alignment::Left));
        virtual ~Label();

    public:
        void setGeometry(Rect rect);
        void setText(const std::u16string text);

        void setColor(u_color color);

        void setAlignment(Alignment align);

        void paint(MonitorDevice *const pMonitorDevice) override;
};

#endif /* SRC_GUI_LABEL_H_ */
