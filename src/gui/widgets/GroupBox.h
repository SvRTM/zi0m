#ifndef GROUPBOX_H
#define GROUPBOX_H

#include "Widget.h"
#include "gui/text/TextCharacters.h"

namespace zi0m
{
class GroupBox : public Widget, public TextCharacters
{
    public:
        explicit GroupBox(Point pos, Size size, Widget *const parent);
        virtual ~GroupBox() {}

    public:
        void setSize(Size size);
        void setFont(const IFont &font);
        void setText(const std::u16string text);
        void setEnabled(bool enabled);

    private:
        void calcPosition();

        void updateAllPosition() override;
        void event(EventType type) override;
        void paint(MonitorDevice *const pMonitorDevice) override;

    private:
        const uint8_t textPadding = 3;
        const uint8_t indent = 5;

        bool isWholeBottomLine;
        bool isVisibleRightLine, isVisibleLeftLine;
        uint8_t indentFrameTop = 0;
        int16_t x2Left = 0, x1Right = 0;
        uint8_t y1Left = 0, y1Right = 0;
};
}
#endif // GROUPBOX_H
