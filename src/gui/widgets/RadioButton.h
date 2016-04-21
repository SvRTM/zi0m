#ifndef RADIOBUTTON_H
#define RADIOBUTTON_H

#include "AbstractButton.h"

namespace zi0m
{
class RadioButton : public AbstractButton
{
    public:
        explicit RadioButton(Point pos, Widget *const parent);
        virtual ~RadioButton() {}

    public:
        bool isChecked() const
        {
            return checked;
        }
        void setChecked(bool checked);

    private:
        void paint(MonitorDevice *const pMonitorDevice) override;

    private:
        static constexpr uint8_t radius = 6;

        bool checked = false;

        static const Rect border;
        const Rect &Border() const
        {
            return border;
        }
};
}
#endif // RADIOBUTTON_H
