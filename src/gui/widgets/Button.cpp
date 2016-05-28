/*
 * Copyright © 2016 Artem Smirnov
 * All right reserved.
 * Author: Artem Smirnov <msvrtm@gmail.com>
 * License: http://www.gnu.org/licenses/gpl.txt
 */

#include "Button.h"

namespace zi0m
{
const Rect Button::border = {2, 2, 4, 4};

Button::Button(Point pos, Size size, Widget *const parent)
    : AbstractButton(pos, size, Alignment::Center, border, parent)
{
    typeId = TypeTag(typeId | TypeTag::BUTTON);

    setBackground(
#ifdef RGB888
    {0x00D6D2D0U}
#elif RGB565
    {0xD69AU}
#endif
    );

    TextCharacters::m_pos = {border.x, border.y};
    TextCharacters::m_size = {geometry().width, geometry().height};
    TextCharacters::updateAbsPosition(absoluteClientPos);
}

void Button::p_setSize()
{
    TextCharacters::m_size = {geometry().width, geometry().height};
}
void Button::p_updateAllPosition()
{
    TextCharacters::updateAbsPosition(absoluteClientPos);
}

void Button::paint(MonitorDevice *const pMonitorDevice)
{
    u_color colorTL, colorBR;

    switch (type)
    {
        case EventType::TouchStart:
        case EventType::TouchEnter:
        {
            colorBR = {COLOR_WHITE};
            colorTL = {COLOR_GRAYD};

            pMonitorDevice->fillRect(screenClient(), background());

            // left
            pMonitorDevice->drawVLine(int16_t(screenClient().x + borderWidth),
                                      int16_t(screenClient().y + borderWidth),
                                      uint16_t(screenClient().height - 3 * borderWidth), {COLOR_GRAY});
            // top
            pMonitorDevice->drawHLine(int16_t(screenClient().x + 2 * borderWidth),
                                      int16_t(screenClient().y + borderWidth),
                                      uint16_t(screenClient().width - 4 * borderWidth), {COLOR_GRAY});

            drawText(pMonitorDevice, color(), 1, 1);
            break;
        }
        case EventType::TouchMove:
            return;
        case EventType::TouchEnd:
        default:
        {
            colorBR = {COLOR_GRAYD};
            colorTL = {COLOR_WHITE};

            pMonitorDevice->fillRect(screenClient(), background());

            // bottom
            pMonitorDevice->drawHLine(int16_t(screenClient().x + borderWidth),
                                      int16_t(screenClient().y + screenClient().height - 2 * borderWidth),
                                      uint16_t(screenClient().width - 3 * borderWidth), {COLOR_GRAY});
            // right
            pMonitorDevice->drawVLine(int16_t(screenClient().x + screenClient().width - 2 *
                                              borderWidth), int16_t(screenClient().y + borderWidth),
                                      uint16_t(screenClient().height - 2 * borderWidth), {COLOR_GRAY});

            drawText(pMonitorDevice);
        }
    }


    // bottom
    pMonitorDevice->drawHLine(screenClient().x,
                              int16_t(screenClient().y + screenClient().height - borderWidth),
                              uint16_t(screenClient().width - borderWidth), colorBR);
    // right
    pMonitorDevice->drawVLine(int16_t(screenClient().x + screenClient().width - borderWidth),
                              screenClient().y, screenClient().height, colorBR);

    // left
    pMonitorDevice->drawVLine(screenClient().x, screenClient().y,
                              uint16_t(screenClient().height - borderWidth), colorTL);
    // top
    pMonitorDevice->drawHLine(screenClient().x, screenClient().y,
                              uint16_t(screenClient().width - borderWidth), colorTL);
}

}
