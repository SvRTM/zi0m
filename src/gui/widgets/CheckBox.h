#ifndef CHECKBOX_H
#define CHECKBOX_H

#include "AbstractButtonASize.h"

namespace zi0m
{
class CheckBox : public AbstractButtonASize
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
        inline State checkState() const
        {
            return state;
        }

        void setTristate(bool tristate = true);
        inline bool isTristate() const
        {
            return tristate;
        }

    private:
        void p_cbReleased() override {}

        void paint(MonitorDevice *const pMonitorDevice) override;

    private:
        State state = State::Unchecked;
        bool tristate = false;
        bool fullUpdate = true;

        static const Rect border;
        inline const Rect &Border() const
        {
            return border;
        }
};
}
#endif // CHECKBOX_H
