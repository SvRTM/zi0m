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

void p_checkbox::drawCheckBox(Point &pos, u_color boxBg,
                              MonitorDevice *const pMonitorDevice, uint16_t bxWidth, uint16_t subzero)
{
    if (bxWidth == 0)
        return;

    // right
    pMonitorDevice->drawVLine(int16_t(pos.x + boxWidth - borderWidth), pos.y,
                              boxWidth, {COLOR_WHITE});
    if (bxWidth > 1)
    {
        // top
        pMonitorDevice->drawHLine(int16_t(pos.x + subzero), pos.y,
                                  uint16_t(boxWidth - borderWidth - subzero), {COLOR_GRAY});
        // right
        pMonitorDevice->drawVLine(int16_t(pos.x + boxWidth - 2 * borderWidth),
                                  int16_t(pos.y + borderWidth), uint16_t(boxWidth - 2 * borderWidth),
        {COLOR_SILVER});
        // bottom
        pMonitorDevice->drawHLine(int16_t(pos.x + (subzero == 0 ? 0 : subzero)),
                                  int16_t(pos.y + boxWidth - borderWidth),
                                  uint16_t(boxWidth - borderWidth - (subzero == 0 ? 0 : subzero)),
        {COLOR_WHITE});
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
                pMonitorDevice->drawVLine(pos.x, pos.y, uint16_t(boxWidth - borderWidth), {COLOR_GRAY});
            // left
            pMonitorDevice->drawVLine(int16_t(pos.x + borderWidth), int16_t(pos.y + borderWidth),
                                      uint16_t(boxWidth - 3 * borderWidth), {COLOR_GRAYD});
        }

        // top
        pMonitorDevice->drawHLine(int16_t(pos.x + (subzero == 0 ? 2 * borderWidth : subzero)),
                                  int16_t(pos.y + borderWidth),
                                  uint16_t(boxWidth - 2 * borderWidth - (subzero == 0 ? 2 * borderWidth : subzero)),
        {COLOR_GRAYD});
        // bottom
        pMonitorDevice->drawHLine(int16_t(pos.x + (subzero == 0 ? borderWidth : subzero)),
                                  int16_t(pos.y + boxWidth - 2 * borderWidth),
                                  uint16_t(boxWidth - (subzero == 0 ? 3 * borderWidth : subzero + borderWidth)),
        {COLOR_SILVER});
    }
}

}
