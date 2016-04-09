/*
 * MainWindow.cpp
 *
 *  Created on: 3 февр. 2016 г.
 *      Author: Artem.Smirnov
 */

#include "MainWindow.h"
#include "gui/widgets/Button.h"
#include "Labels.h"

#include "gui/text/font/PT_Serif_AA_14pt_Regular.h"
#include "gui/text/font/Terminus_24pt_Regular.h"

MainWindow::MainWindow() : Widget({0, 0}, {320, 240})
{
    setupUi();
}

void MainWindow::setupUi()
{
    addWidget(new Header(this));
    addWidget(new Body(this));
}

void MainWindow::event(EventType type)
{
    this->type = type;
}

void MainWindow::paint(MonitorDevice *const pMonitorDevice)
{
    pMonitorDevice->fillRect(screen(), background());
}

// #####################################################
// # # # # # # # # # # # # # # # # # # # # # # # # # # # #
MainWindow::Header::Header(Widget *parent)
#ifdef RGB888
    : Additional({0x00A3D5ACU}),
#elif  RGB565
    :
    Additional({0xA6B5U}),
#endif
Widget({0, 0}, {320, 30}, parent)
{
    // FIXME: replace (320/240) on MAX_WIDTH / MAX_HEIGHT

    const IFont &font = FONT(PT_Serif_AA_14pt_Regular);
    Button *btn = new Button({10, 2}, {80, 25}, this);
    btn->setText(u"← Prev");
    btn->setFont(font);
    addWidget(btn);
    btn = new Button({230, 2}, {80, 25}, this);
    btn->setText(u"Next →");
    btn->setFont(font);
    addWidget(btn);
}

void MainWindow::Header::event(EventType type)
{
    this->type = type;
}
void MainWindow::Header::paint(MonitorDevice *const pMonitorDevice)
{
    pMonitorDevice->fillRect(screen(), background());
}
// # # # # # # # # # # # # # # # # # # # # # # # # # # # #
MainWindow::Body::Body(Widget *parent)
#ifdef RGB888
    : Additional({0x00A3A3D5U})
#elif  RGB565
    : Additional({0xA51AU})
#endif
, Widget({5, 35}, {320 - 5 - 5, 240 - 35 - 5}, parent)
{
    // FIXME: replace (320/240) on MAX_WIDTH / MAX_HEIGHT
    addWidget(new Labels({0, 0}, size(), this));
}

void MainWindow::Body::event(EventType type)
{
    this->type = type;
}
void MainWindow::Body::paint(MonitorDevice *const pMonitorDevice)
{
    pMonitorDevice->fillRect(screen(), background());
}
