#ifndef P_CHECKBOX_H
#define P_CHECKBOX_H

#include "gui/common.h"
#include "gui/io/MonitorDevice.h"

namespace zi0m
{
class p_checkbox final
{
    public:
        static void drawCheckBox(Point &pos,  u_color boxBg, MonitorDevice *const pMonitorDevice,
                                 uint16_t bxWidth = boxWidth, uint16_t subzero = 0);
        static void drawCheckmark(const Point &pos, const u_color color,
                                  MonitorDevice *const pMonitorDevice, const uint8_t stColumn = 0);

    public:
        static constexpr uint8_t checkmark[8] =
        {
            0b00000001,         // 0x01U
            0b00000011,         // 0x03U
            0b00000111,         // 0x07U
            0b10001110,         // 0x8EU
            0b11011100,         // 0xDCU
            0b11111000,         // 0xF8U
            0b01110000,         // 0x70U
            0b00100000          // 0x20U
        };

        static constexpr uint8_t boxWidth = 14;
        static constexpr uint8_t borderWidth = 1;
        static constexpr uint8_t marginLeftRight = 5;
};
}
#endif // P_CHECKBOX_H
