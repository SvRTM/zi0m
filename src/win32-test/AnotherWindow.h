/*
 * AnotherWindow.h
 *
 *  Created on: 14 февр. 2016 г.
 *      Author: Artem.Smirnov
 */

#ifndef GUI_AnotherWindow_H_
#define GUI_AnotherWindow_H_

#include "../gui/Widget.h"
#include <vector>
class AnotherWindow: public Widget
{
    public:
        AnotherWindow(Widget *parent);
        virtual ~AnotherWindow();

        void paint(MonitorDevice *pMonitorDevice) override;
        void setupUi();

        void setBackground(u_color bg);

        u_color background;
};

#endif /* GUI_AnotherWindow_H_ */
