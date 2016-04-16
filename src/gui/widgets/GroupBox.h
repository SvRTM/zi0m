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

    private:
        void calcPosition();
        void p_setSize() override;
        void p_setFont() override;
        void p_setText() override;
        void p_updateAllPosition() override;

        void event(const EventType type) override;
        void paint(MonitorDevice *const pMonitorDevice) override;

    private:
        static constexpr uint8_t textPadding = 3;
        static constexpr uint8_t indent = 5;

        bool isWholeBottomLine;
        bool isVisibleRightLine, isVisibleLeftLine;
        uint8_t indentFrameTop = 0;
        int16_t x2Left = 0, x1Right = 0;
        uint8_t y1Left = 0, y1Right = 0;
};
}
#endif // GROUPBOX_H
