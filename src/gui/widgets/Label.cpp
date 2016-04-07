/*
 * Label.cpp
 *
 *  Created on: 6 марта 2016 г.
 *      Author: Artem.Smirnov
 */

#include "Label.h"

namespace zi0m
{

Label::Label(Widget *parent, Alignment align)
    : Widget(parent), TextCharacters(align)
{
    if (parent)
        setBackground(parent->background());
}

void Label::setGeometry(Rect rect)
{
    TextCharacters::setGeometry({0, 0, rect.width, rect.height});
    Widget::setGeometry(rect);
}

void Label::updateGeometry()
{
    Widget::updateGeometry();
    TextCharacters::updateTextAbsPosition(screen());
}

void Label::setText(const std::u16string text)
{
    TextCharacters::setText(text);
    refresh();
}

void Label::setFont(const IFont &font)
{
    TextCharacters::setFont(font);
    refresh();
}

void Label::setAlignment(Alignment align)
{
    this->align = align;
    refresh();
}

void  Label::setColor(u_color color)
{
    m_color = color;
    refresh();
}

void Label::event(EventType type)
{
    this->type = type;
}

void Label::paint(MonitorDevice *const pMonitorDevice)
{
    if (text().length() == 0)
        return;

    pMonitorDevice->fillRect(screen(), background());

    drawText(pMonitorDevice);
}

}
