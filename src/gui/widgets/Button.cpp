/*
 * Button.cpp
 *
 *  Created on: 2 февр. 2016 г.
 *      Author: Artem.Smirnov
 */

#include "Button.h"

namespace zi0m
{
const Rect Button::border = {2, 2, 2, 2};

Button::Button(Point pos, Size size, Widget *const parent)
    : AbstractButton(pos, size, Alignment::Center, border, parent)
{
    setBackground(
#ifdef RGB888
    {0x00D6D2D0U}
#elif RGB565
    {0xD69AU}
#endif
    );

    TextCharacters::m_pos = 0;
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
            pMonitorDevice->fillRect(screenClient(), background());

            colorBR = {COLOR_WHITE};
            colorTL = {COLOR_GRAYD};

            u_color colorTL2({COLOR_GRAY});

            // left
            pMonitorDevice->fillRect({int16_t(screenClient().x + borderWidth), int16_t(screenClient().y + borderWidth),
                                      borderWidth, uint16_t(screenClient().height - 3 * borderWidth)
                                     }, colorTL2);
            // top
            pMonitorDevice->fillRect({int16_t(screenClient().x + 2 * borderWidth), int16_t(screenClient().y + borderWidth),
                                      uint16_t(screenClient().width - 4 * borderWidth), borderWidth
                                     }, colorTL2);

            drawText(pMonitorDevice, color(), 1, 1);
            break;
        }
        case EventType::TouchMove:
            return;
        case EventType::TouchEnd:
        default:
        {
            pMonitorDevice->fillRect(screenClient(), background());

            colorBR = {COLOR_GRAYD};
            colorTL = {COLOR_WHITE};

            u_color colorBR2({COLOR_GRAY});

            // bottom
            pMonitorDevice->fillRect({int16_t(screenClient().x + borderWidth), int16_t(screenClient().y + screenClient().height - 2 * borderWidth),
                                      uint16_t(screenClient().width - 3 * borderWidth), borderWidth
                                     }, colorBR2);
            // right
            pMonitorDevice->fillRect({int16_t(screenClient().x + screenClient().width - 2 * borderWidth), int16_t(screenClient().y + borderWidth),
                                      borderWidth, uint16_t(screenClient().height - 2 * borderWidth)
                                     }, colorBR2);

            drawText(pMonitorDevice);
        }
    }

    // bottom
    pMonitorDevice->fillRect({screenClient().x, int16_t(screenClient().y + screenClient().height - borderWidth),
                              uint16_t(screenClient().width - borderWidth), borderWidth
                             }, colorBR);
    // right
    pMonitorDevice->fillRect({int16_t(screenClient().x + screenClient().width - borderWidth), screenClient().y,
                              borderWidth, screenClient().height
                             }, colorBR);

    // left
    pMonitorDevice->fillRect({screenClient().x, screenClient().y, borderWidth,
                              uint16_t(screenClient().height - borderWidth)
                             }, colorTL);
    // top
    pMonitorDevice->fillRect({screenClient().x, screenClient().y,
                              uint16_t(screenClient().width - borderWidth), borderWidth
                             }, colorTL);
}

}
