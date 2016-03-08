/*
 * AnotherWindow.cpp
 *
 *  Created on: 14 февр. 2016 г.
 *      Author: Artem.Smirnov
 */

#include "AnotherWindow.h"
#include "../gui/Button.h"

AnotherWindow::AnotherWindow(Widget *parent)
        : Widget(parent)
{
    setGeometry(Rect(20, 30, 120, 100));
    setupUi();
}
AnotherWindow::~AnotherWindow()
{
}

void AnotherWindow::setupUi()
{
    Button *bt = new Button(this);
    bt->setGeometry(Rect(15, 15, 60, 30));
    bt->setText(u"Смирнов @#");
    add(bt);

    setBackground(u_color { 0x008886FAU });
    //setBackground(u_color { 0x00D6D2D0U });
}

void AnotherWindow::paint(MonitorDevice * const pMonitorDevice)
{
    pMonitorDevice->fillRect(screenRect, background);
}

void AnotherWindow::setBackground(u_color bg)
{
    background = bg;
}

