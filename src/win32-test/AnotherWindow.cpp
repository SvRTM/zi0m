/*
 * AnotherWindow.cpp
 *
 *  Created on: 14 февр. 2016 г.
 *      Author: Artem.Smirnov
 */

#include "AnotherWindow.h"
#include "../gui/Button.h"
#include "../gui/Label.h"

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
    //bt->setText(u"Смирнов @#");
    add(bt);

    Label *lb = new Label(this, Alignment::Center);
    lb->setText(u"Ёд 1234567 890 QWErtYu");
    lb->setGeometry(Rect(120, 50, 100, 6));
    add(lb);
    lb = new Label(this, Alignment::Center);
    lb->setText(u"Ё☎д 12345");
    lb->setGeometry(Rect(10, 50, 100, 26));
    add(lb);
    lb = new Label(this, Alignment::Top);
    lb->setText(u"Ё☎д 12345");
    lb->setGeometry(Rect(10, 150, 100, 26));
    add(lb);
    lb = new Label(this, Alignment::Bottom);
    lb->setText(u"Ёд 12345");
    lb->setGeometry(Rect(10, 80, 200, 36));
    add(lb);

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

