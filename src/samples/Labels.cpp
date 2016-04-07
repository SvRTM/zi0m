/*
 * AnotherWindow.cpp
 *
 *  Created on: 14 февр. 2016 г.
 *      Author: Artem.Smirnov
 */

#include "Labels.h"
#include "gui/widgets/Button.h"

#include "gui/text/font/PT_Serif_AA_14pt_Regular.h"
#include "gui/text/font/Terminus_11pt_Regular.h"
#include "gui/text/font/Terminus_24pt_Regular.h"
#include "gui/text/font/Tinos_AA_11pt_Regular.h"


Labels::Labels(Widget *parent)
    : Widget(parent), isEnabledLabels(true), nFont(0)
{
    setGeometry({0, 0, parent->geometry().width, parent->geometry().height});
    setBackground({ 0x008886FAU });
    setupUi();
}

void Labels::setupUi()
{
    fonts.push_back(std::make_pair(&FONT(Terminus_11pt_Regular), u"Terminus_11pt_Regular"));
    fonts.push_back(std::make_pair(&FONT(Terminus_24pt_Regular), u"Terminus_24pt_Regular"));
    fonts.push_back(std::make_pair(&FONT(Tinos_AA_11pt_Regular), u"Tinos_AA_11pt_Regular"));
    fonts.push_back(std::make_pair(&FONT(PT_Serif_AA_14pt_Regular),
                                   u"PT_Serif_AA_14pt_Regular"));

    Button *btn = new Button(this);
    btn->setGeometry({115, 0, 70, 25});
    btn->setText(u"Enable");
    btn->setCbReleased([btn, this]()
    {
        isEnabledLabels = !isEnabledLabels;
        if (isEnabledLabels)
            btn->setText(u"Enable");
        else
            btn->setText(u"Disable");
        for (Widget *const w : labels)
            w->setVisible(isEnabledLabels);
    });
    addWidget(btn);
    btn = new Button(this);
    btn->setGeometry({130, 174, 50, 25});
    btn->setText(u"Font");
    btn->setCbReleased([btn, this]()
    {
        std::pair<const IFont *, std::u16string> p = fonts[++nFont % fonts.size()];
        const IFont &font = *p.first;
        lblFontName->setText(p.second);
        for (Label *w : labels)
            w->setFont(font);
    });
    addWidget(btn);


    u_color bg = {COLOR_24B_GREEN};

    Label *lb = new Label(this, Alignment::Left);
    lb->setGeometry({1, 1, 110, 25});
    lb->setText(u"Left-aligned");
    lb->setBackground(bg);
    addWidget(lb);
    labels.push_back(lb);
    lb = new Label(this, Alignment::Right);
    lb->setGeometry({188, 1, 120, 25});
    lb->setText(u"Right-aligned");
    lb->setBackground(bg);
    addWidget(lb);
    labels.push_back(lb);
    lb = new Label(this, Alignment::Bottom);
    lb->setGeometry({1, 174, 120, 20});
    lb->setText(u"Bottom aligned");
    lb->setBackground(bg);
    addWidget(lb);
    labels.push_back(lb);
    lb = new Label(this, Alignment::Top);
    lb->setGeometry({188, 174, 120, 25});
    lb->setText(u"Top aligned");
    lb->setBackground(bg);
    addWidget(lb);
    labels.push_back(lb);

    lb = new Label(this, Alignment::Center);
    lb->setGeometry({15, 30, 280, 16});
    lb->setText(u"Displaying unknown symbols: 俄罗斯");
    lb->setBackground(bg);
    addWidget(lb);
    labels.push_back(lb);
    lb = new Label(this, Alignment::Center);
    lb->setText(u"Center horizontal and vertical align of an element.");
    lb->setBackground(bg);
    lb->setGeometry(Rect(2, 50, 306, 5));
    addWidget(lb);
    labels.push_back(lb);
    lb = new Label(this, Alignment::Center);
    lb->setText(u"Center horizontal and vertical align of an element.");
    lb->setBackground(bg);
    lb->setGeometry(Rect(2, 60, 306, 30));
    addWidget(lb);
    labels.push_back(lb);

    lblFontName = new Label(this, Alignment::Center);
    lblFontName->setColor({0x00DCE92FU});
    lblFontName->setGeometry(Rect(2, 95, 306, 75));
    addWidget(lblFontName);
    labels.push_back(lblFontName);
}

void Labels::event(EventType type)
{
    this->type = type;
}
void Labels::paint(MonitorDevice *const pMonitorDevice)
{
    pMonitorDevice->fillRect(screen(), background());
}
