#ifndef CHECKBOX_H
#define CHECKBOX_H

#include "Widget.h"
#include "gui/text/TextCharacters.h"

namespace zi0m
{
class CheckBox : public Widget, public TextCharacters
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
        void setAutoSize(bool autoSize);
        void setSize(Size size);
        void setFont(const IFont &font);
        void setText(const std::u16string text);

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
        void updateAllPosition() override;
        void event(EventType type) override;
        void paint(MonitorDevice *const pMonitorDevice) override;

        void autoSize();
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
                        pMonitorDevice->setPoint(x, y, color);
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

        const uint8_t borderWidth = 1;
        const uint8_t marginLeftRight = 5;
        const uint8_t boxWidth = 14;

        State state = State::Unchecked;
        bool tristate = false;

        bool m_autoSize = true;
};
}
#endif // CHECKBOX_H