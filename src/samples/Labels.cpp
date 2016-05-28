/*
 * Copyright © 2016 Artem Smirnov
 * All right reserved.
 * Author: Artem Smirnov <msvrtm@gmail.com>
 * License: http://www.gnu.org/licenses/gpl.txt
 */

#include "Labels.h"
#include "gui/widgets/Button.h"


Labels::Labels(Point pos, Size size, Widget *parent)
    : AbstractBody(pos, size, parent), isEnabledLabels(true)
{
#ifdef RGB888
    setBackground({ 0X007092BEU });
#elif  RGB565
    setBackground({ 0x7497U });
#endif
    setupUi();
}

void Labels::setupUi()
{
    Button *btn = new Button({115, 0}, {70, 25}, this);
    btn->setText(u"Enable");
    btn->setCbReleased([btn, this]()
    {
        isEnabledLabels = !isEnabledLabels;
        if (isEnabledLabels)
            btn->setText(u"Enable");
        else
            btn->setText(u"Disable");
        for (AbstractTextWidget *const w : smplWidgets)
            w->setEnabled(isEnabledLabels);
    });
    addWidget(btn);


    u_color bg = {COLOR_GREEN};

    Label *lb = new Label({1, 1}, {110, 25}, this, Alignment::Left);
    lb->setText(u"Left-aligned");
    lb->setBackground(bg);
    addWidget(lb);
    smplWidgets.push_back(lb);
    lb = new Label({188, 1}, {120, 25}, this, Alignment::Right);
    lb->setText(u"Right-aligned");
    lb->setBackground(bg);
    addWidget(lb);
    smplWidgets.push_back(lb);
    lb = new Label({1, 160}, {120, 39}, this, Alignment::Bottom);
    lb->setText(u"Bottom aligned");
    lb->setBackground(bg);
    addWidget(lb);
    smplWidgets.push_back(lb);
    lb = new Label({188, 160}, {120, 39}, this, Alignment::Top);
    lb->setText(u"Top aligned");
    lb->setBackground(bg);
    addWidget(lb);
    smplWidgets.push_back(lb);

    lb = new Label({15, 30}, {280, 16}, this, Alignment::Center);
    lb->setText(u"Displaying unknown symbols: 俄罗斯");
    lb->setBackground(bg);
    addWidget(lb);
    smplWidgets.push_back(lb);
    lb = new Label({2, 50}, {306, 5}, this, Alignment::Center);
    lb->setText(u"Center horizontal and vertical align of an element.");
    lb->setBackground(bg);
    addWidget(lb);
    smplWidgets.push_back(lb);
    lb = new Label({2, 60}, {306, 30}, this, Alignment::Center);
    lb->setText(u"Center horizontal and vertical align of an element.");
    lb->setBackground(bg);
    addWidget(lb);
    smplWidgets.push_back(lb);

    pLblFontName = new Label({2, 95}, {306, 55}, this, Alignment::Center);
#ifdef RGB888
    pLblFontName->setColor({0x00DCE92FU});
#elif  RGB565
    pLblFontName->setColor({0xDF45U});
#endif
    addWidget(pLblFontName);
    smplWidgets.push_back(pLblFontName);
}

void Labels::setFontWidgtes(std::pair<const IFont *, std::u16string> data)
{
    const IFont &font = *data.first;
    pLblFontName->setText(data.second);
    for (AbstractTextWidget *const w : smplWidgets)
        w->setFont(font);
}
