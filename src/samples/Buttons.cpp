/*
 * AnotherWindow.cpp
 *
 *  Created on: 14 февр. 2016 г.
 *      Author: Artem.Smirnov
 */

#include "Buttons.h"
#include "gui/widgets/CheckBox.h"
#include "gui/widgets/RadioButton.h"

Buttons::Buttons(Point pos, Size size, Widget *parent)
    : Widget(pos, size, parent)
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

    RadioButton *rb  = new RadioButton({5, 125}, this);
    rb->setText(u"RadioButton");
    rb->setBackground(bg);
    addWidget(rb);
    smplWidgets.push_back(rb);
    rb  = new RadioButton({5, 150}, this);
    rb->setText(u"Checked");
    rb->setChecked(true);
    rb->setEnabled(false);
    addWidget(rb);
    smplWidgets.push_back(rb);
}

void Buttons::setFontWidgtes(std::pair<const IFont *, std::u16string> data)
{
    const IFont &font = *data.first;
    for (zi0m::TextCharacters *const w : smplWidgets)
        dynamic_cast<AbstractButton *const>(w)->setFont(font);
    refresh();
}

void Buttons::event(EventType type)
{
    this->type = type;
}
void Buttons::paint(MonitorDevice *const pMonitorDevice)
{
    pMonitorDevice->fillRect(screen(), background());
}
