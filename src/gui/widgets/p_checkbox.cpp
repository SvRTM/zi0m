#include "p_checkbox.h"

namespace zi0m
{

constexpr uint8_t p_checkbox::checkmark[8];

void p_checkbox::drawCheckmark(const Point &pos, const u_color color,
                               MonitorDevice *const pMonitorDevice, const uint8_t stColumn)
{
    int16_t y  = pos.y + 1 + 2 * borderWidth;
    for (uint8_t  nRow = 0; nRow < sizeof(checkmark); ++nRow)
    {
        int16_t x = pos.x + 1 + 2 * borderWidth + stColumn;
        for (uint8_t width = stColumn; width < 8; ++width)
        {
            const uint8_t nBit = 7 - (width % 8);
            const bool px = checkmark[nRow] >> nBit & 0x01;
            if (px)
                pMonitorDevice->drawPoint(x, y, color);
            x++;
        }
        y++;
    }
}

void p_checkbox::drawCheckBox(Point &pos,
                              u_color boxBg, MonitorDevice *const pMonitorDevice, uint16_t bxWidth, uint16_t subzero)
{
    if (bxWidth == 0)
        return;

    u_color colorBR = {COLOR_WHITE};
    u_color colorBR2 = {COLOR_SILVER};
    u_color colorTL = {COLOR_GRAY};
    u_color colorTL2({COLOR_GRAYD});

    // right
    pMonitorDevice->fillRect({int16_t(pos.x + boxWidth - borderWidth), pos.y,
                              borderWidth, boxWidth
                             }, colorBR);
    if (bxWidth > 1)
    {
        // top
        pMonitorDevice->fillRect({int16_t(pos.x + subzero), pos.y,
                                  uint16_t(boxWidth - borderWidth - subzero), borderWidth
                                 }, colorTL);
        // right
        pMonitorDevice->fillRect({int16_t(pos.x + boxWidth - 2 * borderWidth), int16_t(pos.y + borderWidth),
                                  borderWidth, uint16_t(boxWidth - 2 * borderWidth)
                                 }, colorBR2);
        // bottom
        pMonitorDevice->fillRect({int16_t(pos.x + (subzero == 0 ? 0 : subzero)), int16_t(pos.y + boxWidth - borderWidth),
                                  uint16_t(boxWidth - borderWidth - (subzero == 0 ? 0 : subzero)), borderWidth
                                 }, colorBR);
    }

    if (bxWidth > 2)
    {
        // box
        pMonitorDevice->fillRect({int16_t(pos.x + (subzero == 0 ? 2 * borderWidth : subzero)), int16_t(pos.y + 2 * borderWidth),
                                  uint16_t(bxWidth - (subzero == 0 ? 4 * borderWidth : 2 * borderWidth)), uint16_t(boxWidth - 4 * borderWidth)
                                 }, boxBg);

        if (subzero <= 1)
        {
            // left
            if (subzero == 0)
                pMonitorDevice->fillRect({pos.x, pos.y, borderWidth, uint16_t(boxWidth - borderWidth)
                                         }, colorTL);
            // left
            pMonitorDevice->fillRect({int16_t(pos.x + borderWidth), int16_t(pos.y + borderWidth),
                                      borderWidth, uint16_t(boxWidth - 3 * borderWidth)
                                     }, colorTL2);
        }

        // top
        pMonitorDevice->fillRect({int16_t(pos.x + (subzero == 0 ? 2 * borderWidth : subzero)), int16_t(pos.y + borderWidth),
                                  uint16_t(boxWidth - 2 * borderWidth - (subzero == 0 ? 2 * borderWidth : subzero)), borderWidth
                                 }, colorTL2);
        // bottom
        pMonitorDevice->fillRect({int16_t(pos.x + (subzero == 0 ? borderWidth : subzero)), int16_t(pos.y + boxWidth - 2 * borderWidth),
                                  uint16_t(boxWidth - (subzero == 0 ? 3 * borderWidth : subzero + borderWidth)), borderWidth
                                 }, colorBR2);
    }
}

}
