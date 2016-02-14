/*
 * MainWindow.cpp
 *
 *  Created on: 3 февр. 2016 г.
 *      Author: Artem.Smirnov
 */

#include "MainWindow.h"
#include "../gui/Button.h"

MainWindow::MainWindow()
        : Widget()
{
    setGeometry(Rect(0, 0, 320, 240));
    setupUi();
}
MainWindow::~MainWindow()
{
}

void MainWindow::setupUi()
{
    Button *bt = new Button(this);
    bt->setGeometry(Rect(15, 15, 60, 30));
    add(bt);

    setBackground(u_color { 0x00C8F6FAU });
}

void MainWindow::paint(MonitorDevice *pMonitorDevice)
{
    if (_refresh)
    {
        pMonitorDevice->fillRect(
                Rect(geometry()->x, geometry()->y, geometry()->width,
                        geometry()->height), background);
        _refresh = false;
    }

    Widget::paint(pMonitorDevice);
}

void MainWindow::setBackground(u_color bg)
{
    background = bg;
}

