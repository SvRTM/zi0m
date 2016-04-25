/*
 * Label.cpp
 *
 *  Created on: 6 марта 2016 г.
 *      Author: Artem.Smirnov
 */

#include "Label.h"

namespace zi0m
{
Label::Label(Point pos, Size size, Widget *const parent, Alignment align)
    : AbstractTextWidget(pos, size, align, parent)
{
    TextCharacters::m_pos = 0;
    TextCharacters::m_size = {geometry().width, geometry().height};
    TextCharacters::updateAbsPosition(absoluteClientPos);
}

void Label::p_setSize()
{
    TextCharacters::m_size = {geometry().width, geometry().height};
}
void Label::p_updateAllPosition()
{
    TextCharacters::updateAbsPosition(absoluteClientPos);
}

void Label::paint(MonitorDevice *const pMonitorDevice)
{
    if (text().length() == 0)
        return;

    pMonitorDevice->fillRect(screen(), background());

    drawText(pMonitorDevice);
}

}
