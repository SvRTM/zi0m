/*
 * AnotherWindow.cpp
 *
 *  Created on: 14 февр. 2016 г.
 *      Author: Artem.Smirnov
 */

#include "AnotherWindow.h"
#include "gui/Button.h"
#include "gui/Label.h"

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
    addWidget(bt);

    Label *lb = new Label(this, Alignment::Center);
    lb->setText(u"Ёд 1234567 890 QWErtYu");
    lb->setText(u" 2.~`gj+.,^Щщу 1234567890");
    lb->setGeometry(Rect(120, 55, 100, 6));
    addWidget(lb);
    lb = new Label(this, Alignment::Center);
    lb->setText(u"Ё☎д 12345");
    lb->setGeometry(Rect(10, 50, 100, 16));
    addWidget(lb);
    lb = new Label(this, Alignment::Top);
    lb->setText(u"Ё☎д 12345");
    lb->setGeometry(Rect(10, 150, 100, 26));
    addWidget(lb);
    lb = new Label(this, Alignment::Bottom | Alignment::Right);
    lb->setText(u"Ёд 12345");
    lb->setGeometry(Rect(10, 80, 100, 100));
    addWidget(lb);
    lb = new Label(this, Alignment::Top | Alignment::HCenter);
    lb->setText(u"Ёд 12345");
    lb->setGeometry(Rect(120, 80, 100, 100));
    addWidget(lb);

    setBackground(u_color { 0x008886FAU });
    //setBackground(u_color { 0x00D6D2D0U });
}

void AnotherWindow::paint(MonitorDevice *const pMonitorDevice)
{
    pMonitorDevice->fillRect(screenRect, background);
}

void AnotherWindow::setBackground(u_color bg)
{
    background = bg;
}

