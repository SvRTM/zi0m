/*
 * MainWindow.h
 *
 *  Created on: 3 февр. 2016 г.
 *      Author: Artem.Smirnov
 */

#ifndef GUI_MAINWINDOW_H_
#define GUI_MAINWINDOW_H_

#include "gui/widgets/Widget.h"

using namespace zi0m;

class MainWindow final : public Widget
{
    public:
        MainWindow();
        virtual ~MainWindow() {}

    private:
        void paint(MonitorDevice *const pMonitorDevice) override;
        void event(EventType type) override;

        void setupUi();

    private:
        class Header final : public Widget
        {
            public:
                Header(Widget *parent);
                virtual ~Header() {}

            private:
                void paint(MonitorDevice *const pMonitorDevice) override;
                void event(EventType type) override;
        };

        class Body final : public Widget
        {
            public:
                Body(Widget *parent);
                virtual ~Body() {}

            private:
                void paint(MonitorDevice *const pMonitorDevice) override;
                void event(EventType type) override;
        };
};

#endif /* GUI_MAINWINDOW_H_ */
