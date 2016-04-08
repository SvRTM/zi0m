/*
 * Label.cpp
 *
 *  Created on: 6 марта 2016 г.
 *      Author: Artem.Smirnov
 */

#include "Label.h"

namespace zi0m
{

Label::Label(Point pos, Size size, Widget *parent, Alignment align)
    : Widget(pos, size, parent)
    , TextCharacters({0, 0}, {size.width, size.height}, align)
{
    if (parent)
        setBackground(parent->background());
    TextCharacters::updateAbsPosition(absolutePos);
}

void Label::setSize(Size size)
{
    TextCharacters::setSize({size.width, size.height});
    Widget::setSize(size);
}

void Label::updateAllPosition()
{
    Widget::updateAllPosition();
    TextCharacters::updateAbsPosition(absolutePos);
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
