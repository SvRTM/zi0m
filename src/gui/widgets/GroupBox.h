#ifndef GROUPBOX_H
#define GROUPBOX_H

#include "Widget.h"
#include "AbstractButton.h"

namespace zi0m
{
class GroupBox : public AbstractTextWidget
{
    public:
        explicit GroupBox(Point pos, Size size, Widget *const parent);
        virtual ~GroupBox() {}

    public:
        bool isCheckable() const
        {
            return checkable;
        }
        void setCheckable(bool checkable);
        bool isChecked() const
        {
            return checked;
        }
        void setChecked(bool checked);

        void setAlignment(Alignment align);
        inline Alignment alignment()
        {
            return alignCenter ? Alignment((alignment()^Alignment::Left) | Alignment::HCenter) :
                   alignment();
        }

    private:
        void calcPosition();
        void p_setSize() override;
        void p_setFont() override;
        void p_setText() override;
        void p_updateAllPosition() override;

        void event(const EventType type, const Point &pos) override;
        void paint(MonitorDevice *const pMonitorDevice) override;

        void paintCheckBox(MonitorDevice *const pMonitorDevice);

    private:
        static constexpr uint8_t textPadding = 2;
        static constexpr uint8_t indent = 5;

        bool isWholeBottomLine;
        bool isVisibleRightLine, isVisibleLeftLine;
        uint8_t indentFrameTop = 0;
        int16_t x2Left = 0, x1Right = 0;
        uint8_t y1Left = 0, y1Right = 0;

        bool checkable = false;
        bool checked = true;

        bool alignCenter = false;


        void drawCheckmark(const Point chPos, const uint8_t stColumn , const u_color color,
                           MonitorDevice *const pMonitorDevice)
        {
            int16_t y  = chPos.y + 1 + 2 * borderWidth;
            for (uint8_t  nRow = 0; nRow < sizeof(checkmark); ++nRow)
            {
                int16_t x = chPos.x + 1 + 2 * borderWidth + stColumn;
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

        //
        static constexpr uint8_t marginLeftRight = 5;

        EventType typeCheckBox = EventType::None;
        bool isEnableTouchLeave = false;

        Rect border;
        inline const Rect &Border() const
        {
            return border;
        }
};
}
#endif // GROUPBOX_H
