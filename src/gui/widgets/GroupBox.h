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
        virtual ~GroupBox() = default;

    public:
        inline bool isCheckable() const
        {
            return checkable;
        }
        void setCheckable(bool checkable);
        inline bool isChecked() const
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
        void prepareAlignHCenter(Alignment align);
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

        bool isWholeBottomLine = true;
        bool isVisibleRightLine = true, isVisibleLeftLine = true;
        uint8_t indentFrameTop = 0;
        int16_t x2Left = 0, x1Right = 0;
        uint8_t y1Left = 0, y1Right = 0;

        bool checkable = false;
        bool checked = true;

        bool alignCenter = false;


    private:
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
