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
        const uint8_t elementWidth() const override;
        void paint(MonitorDevice *const pMonitorDevice) override;

    private:
        const uint8_t radius = 6;

        bool checked = false;
};
}
#endif // RADIOBUTTON_H
