/*
 * Label.cpp
 *
 *  Created on: 6 марта 2016 г.
 *      Author: Artem.Smirnov
 */

#include "Label.h"

Label::Label(Widget *parent, Alignment align)
    : Widget(parent), TextCharacters(align)
{
}
Label::~Label()
{
}

void Label::setGeometry(Rect rect)
{
    Widget::setGeometry(rect);
    setAbsolutePosition(screen());
}

void Label::setText(const std::u16string text)
{
    TextCharacters::setText(text);
    refresh();
}

void Label::setAlignment(Alignment align)
{
    TextCharacters::setAlignment(align);
    refresh();
}

void  Label::setColor(u_color color)
{
    TextCharacters::setColor(color);
    refresh();
}

void Label::paint(MonitorDevice *const pMonitorDevice)
{
    if (text().length() == 0)
        return;

    pMonitorDevice->fillRect(screen(), background());

    drawText(pMonitorDevice);
}

