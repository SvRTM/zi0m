/*
 * MainWindow.cpp
 *
 *  Created on: 3 февр. 2016 г.
 *      Author: Artem.Smirnov
 */

#include "MainWindow.h"
#include "gui/widgets/Button.h"
#include "AnotherWindow.h"

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
    //setBackground(u_color { 0x00D6D2D0U });

    Button *bt = new Button(this);
    bt->setGeometry(Rect(15, 15, 60, 30));
    bt->setText(u"Артём");
    addWidget(bt);

    Widget *aw = new AnotherWindow(this);
    //aw->setGeometry(Rect(20, 30, 120, 100));
    addWidget(aw);
}

void MainWindow::event(EventType type)
{
    this->type = type;
}

void MainWindow::paint(MonitorDevice *const pMonitorDevice)
{
    pMonitorDevice->fillRect(screen(), background());
}
