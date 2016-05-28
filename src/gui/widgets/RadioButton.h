/*
 * Copyright © 2016 Artem Smirnov
 * All right reserved.
 * Author: Artem Smirnov <msvrtm@gmail.com>
 * License: http://www.gnu.org/licenses/gpl.txt
 */

#ifndef RADIOBUTTON_H
#define RADIOBUTTON_H

#include "AbstractButtonASize.h"

namespace zi0m
{
class RadioButton : public AbstractButtonASize
{
    public:
        explicit RadioButton(Point pos, Widget *const parent);
        virtual ~RadioButton() = default;

    public:
        inline bool isChecked() const
        {
            return checked;
        }
        void setChecked(bool checked);

    private:
        void p_cbReleased() override;
        void paint(MonitorDevice *const pMonitorDevice) override;


    private:
        static constexpr uint8_t radius = 6;

        bool checked = false;
        bool fullUpdate = true;

        static const Rect border;
        inline const Rect &Border() const
        {
            return border;
        }
};
}
#endif // RADIOBUTTON_H
