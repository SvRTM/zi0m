/*
 * Copyright © 2016 Artem Smirnov
 * All right reserved.
 * Author: Artem Smirnov <msvrtm@gmail.com>
 * License: http://www.gnu.org/licenses/gpl.txt
 */

#include "Buttons.h"
#include "gui/widgets/CheckBox.h"
#include "gui/widgets/RadioButton.h"

Buttons::Buttons(Point pos, Size size, Widget *parent)
    : AbstractBody(pos, size, parent)
{
#ifdef RGB888
    setBackground({ 0x00EFE4B0U });
#elif  RGB565
    setBackground({ 0xEF36U });
#endif
    setupUi();
}

void Buttons::setupUi()
{
    u_color bg = {COLOR_SNOW};

    CheckBox *ch  = new CheckBox({5, 5}, this);
    ch->setText(u"tri-state checkbox");
    ch->setTristate(true);
    ch->setBackground(bg);
    addWidget(ch);
    smplWidgets.push_back(ch);
    ch  = new CheckBox({5, 30}, this);
    ch->setText(u"Partially checked");
    ch->setTristate(true);
    ch->setState(CheckBox::State::PartiallyChecked);
    ch->setBackground(bg);
    addWidget(ch);
    smplWidgets.push_back(ch);
    ch  = new CheckBox({5, 55},  this);
    ch->setText(u"Partially checked");
    ch->setEnabled(false);
    ch->setTristate(true);
    ch->setState(CheckBox::State::PartiallyChecked);
    addWidget(ch);
    smplWidgets.push_back(ch);
    ch  = new CheckBox({5, 80}, this);
    ch->setText(u"Checked");
    ch->setEnabled(false);
    ch->setState(CheckBox::State::Checked);
    addWidget(ch);
    smplWidgets.push_back(ch);
    ch  = new CheckBox({105, 80}, this);
    ch->setText(u"Checkbox");
    addWidget(ch);
    smplWidgets.push_back(ch);
    ch  = new CheckBox({5, 100}, this);
    ch->setBackground(bg);
    addWidget(ch);
    smplWidgets.push_back(ch);

    RadioButton *rb1  = new RadioButton({5, 125}, this);
    rb1->setText(u"RadioButton 1");
    rb1->setBackground(bg);
    addWidget(rb1);
    smplWidgets.push_back(rb1);
    RadioButton *rb  = new RadioButton({5, 150}, this);
    rb->setText(u"Checked");
    rb->setChecked(true);
    rb->setEnabled(false);
    addWidget(rb);
    smplWidgets.push_back(rb);
    RadioButton *rb2  = new RadioButton({135, 125}, this);
    rb2->setText(u"RadioButton 2");
    rb2->setBackground(bg);
    addWidget(rb2);
    smplWidgets.push_back(rb2);
}

void Buttons::setFontWidgtes(std::pair<const IFont *, std::u16string> data)
{
    const IFont &font = *data.first;
    for (AbstractTextWidget *const w : smplWidgets)
        w->setFont(font);
    refresh();
}
