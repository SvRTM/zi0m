/*
 * MainWindow.h
 *
 *  Created on: 3 февр. 2016 г.
 *      Author: Artem.Smirnov
 */

#ifndef GUI_MAINWINDOW_H_
#define GUI_MAINWINDOW_H_

#include "../gui/Widget.h"
#include <vector>
class MainWindow: public Widget
{
    public:
        MainWindow();
        virtual ~MainWindow();

    public:
        void paint(MonitorDevice *const pMonitorDevice) override;
        void setBackground(u_color bg);

    private:
        void setupUi();

    private:
        u_color background;
};

#endif /* GUI_MAINWINDOW_H_ */
