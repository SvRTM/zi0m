/*
 * AnotherWindow.cpp
 *
 *  Created on: 14 февр. 2016 г.
 *      Author: Artem.Smirnov
 */

#include "AnotherWindow.h"
#include "gui/Button.h"
#include "gui/Label.h"

#include "gui/font/Tinos_AA_11pt_Regular.h"
#include "gui/font/Terminus_24pt_Regular.h"


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
    bt->setVisible(false);
    addWidget(bt);

    //u_color color = {0xFF420D0D};
    // u_color color = {0xFFAA0000U};
    //u_color color = {COLOR_24B_PURPLE};
    u_color color = {COLOR_24B_BLACK};
    u_color bg = {COLOR_24B_GREEN};

    Label *lb = new Label(this, Alignment::Center);
    //lb->setText(u"Ёд 1234567 890 QWErtYu");
    lb->setText(u" 2.~`gj+.,^Щщу 1234567890");
    lb->setColor(color);
    lb->setBackground(bg);
    lb->setVisible(false);
    lb->setGeometry(Rect(120, 55, 100, 6));
    addWidget(lb);
    lb = new Label(this, Alignment::Center);
    lb->setText(u"Ё☎д 12345");
    lb->setColor(color);
    lb->setBackground(bg);
    lb->setVisible(false);
    lb->setGeometry(Rect(10, 50, 100, 16));
    addWidget(lb);
    lb = new Label(this, Alignment::Top);
    lb->setText(u"Ё☎д 12345");
    lb->setColor(color);
    lb->setBackground(bg);
    lb->setGeometry(Rect(10, 150, 100, 26));
    addWidget(lb);
    lb = new Label(this, (Alignment) (Alignment::Bottom | Alignment::Right));
    lb->setFont(Singleton<Terminus_24pt_Regular>::instance());
    lb->setText(u"Ёд 1234");
    lb->setColor(color);
    lb->setBackground(bg);
    lb->setGeometry(Rect(10, 80, 100, 100));
    addWidget(lb);
    lb = new Label(this, (Alignment) (Alignment::Top | Alignment::HCenter));
    lb->setFont(Singleton<Tinos_AA_11pt_Regular>::instance());
    lb->setText(u" Ёд 12345");
    lb->setColor(color);
    lb->setBackground(bg);
    lb->setVisible(false);
    lb->setGeometry(Rect(120, 80, 100, 100));
    addWidget(lb);
    lb = new Label(this, (Alignment) (Alignment::Top | Alignment::HCenter));
    lb->setFont(Singleton<Tinos_AA_11pt_Regular>::instance());
    lb->setText(u" Ёд 12345");
    lb->setColor(color);
    lb->setBackground(bg);
    lb->setGeometry(Rect(120, 10, 100, 30));

    addWidget(lb);

    setBackground({ 0x008886FAU });
    //setBackground(u_color { 0x00D6D2D0U });
}

void AnotherWindow::paint(MonitorDevice *const pMonitorDevice)
{
    pMonitorDevice->fillRect(screenRect, background());
}
