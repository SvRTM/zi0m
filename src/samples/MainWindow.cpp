/*
 * MainWindow.cpp
 *
 *  Created on: 3 февр. 2016 г.
 *      Author: Artem.Smirnov
 */

#include "MainWindow.h"
#include "gui/widgets/Button.h"

#include "Buttons.h"
#include "GroupBoxs.h"
#include "Labels.h"

#include "gui/text/font/PT_Serif_AA_14pt_Regular.h"
#include "gui/text/font/Terminus_11pt_Regular.h"
#include "gui/text/font/Terminus_24pt_Regular.h"
#include "gui/text/font/Tinos_AA_11pt_Regular.h"

MainWindow::MainWindow() : Widget({0, 0}, {320, 240})
{
    setupUi();
}

void MainWindow::setupUi()
{
    addWidget(new Header(this));
    addWidget(new Body(this));
}

void MainWindow::event(const EventType type, const Point &pos)
{
    this->type = type;
}

void MainWindow::paint(MonitorDevice *const pMonitorDevice)
{
    pMonitorDevice->fillRect(screen(), background());
}

// #####################################################
// # # # # # # # # # # # # # # # # # # # # # # # # # # # #
MainWindow::Header::Header(Widget *parent) :
#ifdef RGB888
    Additional({0x00A3D5ACU}),
#elif  RGB565
    Additional({0xA6B5U}),
#endif
           Widget({0, 0}, {320, 30}, parent)
{
    // FIXME: replace (320/240) on MAX_WIDTH / MAX_HEIGHT

    fonts = {std::make_pair(&FONT(Terminus_11pt_Regular), u"Terminus_11pt_Regular")
             , std::make_pair(&FONT(Terminus_24pt_Regular), u"Terminus_24pt_Regular")
             , std::make_pair(&FONT(Tinos_AA_11pt_Regular), u"Tinos_AA_11pt_Regular")
             , std::make_pair(&FONT(PT_Serif_AA_14pt_Regular), u"PT_Serif_AA_14pt_Regular")
            };

    const IFont &font = FONT(PT_Serif_AA_14pt_Regular);
    Button *btn = new Button({10, 2}, {80, 25}, this);
    btn->setText(u"← Prev");
    btn->setFont(font);
    addWidget(btn);
    btn->setCbReleased([this]()
    {
        const MainWindow *main = static_cast<const MainWindow *>(this->parent());
        main->bodys[iWidget-- % main->bodys.size()]->setVisible(false);
        pBodyWidget = main->bodys[iWidget % main->bodys.size()];
        pBodyWidget->setVisible(true);
    });

    btn = new Button({135, 2}, {50, 25}, this);
    btn->setText(u"Font");
    addWidget(btn);
    btn->setCbReleased([this]()
    {
        std::pair<const IFont *, std::u16string> p = fonts[++nFont % fonts.size()];
        // FIXME: initialize differently
        if (pBodyWidget == nullptr)
        {
            const MainWindow *main = static_cast<const MainWindow *>(this->parent());
            pBodyWidget = main->bodys[iWidget % main->bodys.size()];
        }
        pBodyWidget->setFontWidgtes(p);
    });

    btn = new Button({230, 2}, {80, 25}, this);
    btn->setText(u"Next →");
    btn->setFont(font);
    addWidget(btn);
    btn->setCbReleased([this]()
    {
        const MainWindow *main = static_cast<const MainWindow *>(this->parent());
        main->bodys[iWidget++ % main->bodys.size()]->setVisible(false);
        pBodyWidget = main->bodys[iWidget % main->bodys.size()];
        pBodyWidget->setVisible(true);
    });
}

void MainWindow::Header::event(const EventType type, const Point &pos)
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

    GroupBoxs *pGrBoxs = new GroupBoxs({0, 0}, size(), this);
    Buttons *pButtons =  new Buttons({0, 0}, size(), this);
    Labels *pLabels = new Labels({0, 0}, size(), this);
    pLabels->setVisible(false);
    pButtons->setVisible(false);

    addWidget(pGrBoxs);
    addWidget(pButtons);
    addWidget(pLabels);

    static_cast<MainWindow *>(parent)->bodys = {pGrBoxs, pButtons, pLabels};
}

void MainWindow::Body::event(const EventType type, const Point &pos)
{
    this->type = type;
}
void MainWindow::Body::paint(MonitorDevice *const pMonitorDevice)
{
    pMonitorDevice->fillRect(screen(), background());
}
