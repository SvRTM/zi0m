/*
 * Label.h
 *
 *  Created on: 6 марта 2016 г.
 *      Author: Artem.Smirnov
 */

#ifndef SRC_GUI_LABEL_H_
#define SRC_GUI_LABEL_H_

#include "Widget.h"

#include <string>

class Label: public Widget
{
    public:
        Label(Widget *parent);
        virtual ~Label();

        void setText(const std::u16string &str);

        void paint(MonitorDevice *pMonitorDevice) override;

    private:
         const std::u16string *m_pText;
};

#endif /* SRC_GUI_LABEL_H_ */
