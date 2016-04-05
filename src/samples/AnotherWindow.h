/*
 * AnotherWindow.h
 *
 *  Created on: 14 февр. 2016 г.
 *      Author: Artem.Smirnov
 */

#ifndef GUI_AnotherWindow_H_
#define GUI_AnotherWindow_H_

#include "gui/widgets/Widget.h"

using namespace zi0m;

class AnotherWindow: public Widget
{
    public:
        AnotherWindow(Widget *parent);
        virtual ~AnotherWindow();

    public:
        void paint(MonitorDevice *const pMonitorDevice) override;

    private:
        void setupUi();
        void event(EventType type) override;
};

#endif /* GUI_AnotherWindow_H_ */
