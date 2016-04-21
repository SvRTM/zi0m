#ifndef CHECKBOX_H
#define CHECKBOX_H

#include "AbstractButton.h"

namespace zi0m
{
class CheckBox : public AbstractButton
{
    public:
        explicit CheckBox(Point pos, Widget *const parent);
        virtual ~CheckBox() {}

        enum class State
        {
            Unchecked,
            PartiallyChecked,
            Checked
        };

    public:
        void setState(State state);
        State checkState() const
        {
            return state;
        }
        void setTristate(bool tristate = true);
        bool isTristate() const
        {
            return tristate;
        }

    private:
        void paint(MonitorDevice *const pMonitorDevice) override;

        void drawCheckmark(const Point chPos, const u_color color,
                           MonitorDevice *const pMonitorDevice)
        {
            int16_t y  = chPos.y + 1 + 2 * borderWidth;
            for (uint8_t  nRow = 0; nRow < sizeof(checkmark); ++nRow)
            {
                int16_t x = chPos.x + 1 + 2 * borderWidth;
                for (uint8_t width = 0; width < 8; ++width)
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

    private:
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

        static constexpr uint8_t borderWidth = 1;
        static constexpr uint8_t boxWidth = 14;

        State state = State::Unchecked;
        bool tristate = false;

        static const Rect border;
        inline const Rect &Border() const
        {
            return border;
        }
};
}
#endif // CHECKBOX_H
