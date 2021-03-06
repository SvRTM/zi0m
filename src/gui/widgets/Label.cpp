/*
 * Copyright © 2016 Artem Smirnov
 * All right reserved.
 * Author: Artem Smirnov <msvrtm@gmail.com>
 * License: http://www.gnu.org/licenses/gpl.txt
 */

#include "Label.h"

namespace zi0m
{
Label::Label(Point pos, Size size, Widget *const parent, Alignment align)
    : AbstractTextWidget(pos, size, align, parent)
{
    typeId = TypeTag(typeId | TypeTag::LABEL);

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
