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


    private:
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
