#include "CheckBox.h"
#include "p_checkbox.h"

namespace zi0m
{
const Rect CheckBox::border = p_checkbox::marginLeftRight + p_checkbox::boxWidth +
                              p_checkbox::marginLeftRight;

CheckBox::CheckBox(Point pos, Widget *const parent)
    : AbstractButton(pos, border, parent)
{
    init();
}

void CheckBox::setState(State state)
{
    this->state = state;
    refresh();
}

void CheckBox::setTristate(bool tristate)
{
    this->tristate = tristate;
    refresh();
}

void CheckBox::paint(MonitorDevice *const pMonitorDevice)
{
    u_color boxBg;
    switch (type)
    {
        case EventType::TouchStart:
        case EventType::TouchEnter:
            boxBg = {COLOR_SILVER};
            break;
        case EventType::TouchMove:
            return;
        case EventType::TouchEnd:
        {
            switch (state)
            {
                case State::Unchecked:
                    if (tristate)
                    {
                        state = State::PartiallyChecked;
                        break;
                    }
                case State::PartiallyChecked:
                    state = State::Checked;
                    break;
                case State::Checked:
                    state = State::Unchecked;
            }
        }
        default:
            boxBg = { tristate &&State::PartiallyChecked == state
                      ? COLOR_LAVENDER_BLUSH
                      : (isEnabled()
                         ? COLOR_WHITE : COLOR_SILVER)
                };
    }
    pMonitorDevice->fillRect(screenClient(), background());

    Point chPos = {p_checkbox::marginLeftRight, int16_t((size().height - p_checkbox::boxWidth) / 2)};
    chPos.x += screenClient().x;
    chPos.y += screenClient().y;

    p_checkbox::drawCheckBox(chPos, boxBg, pMonitorDevice);

    if (State::Unchecked != state)
    {
        u_color chmarkClr;
        chmarkClr =  {isEnabled()
                      ? (State::PartiallyChecked == state
                         ? COLOR_GRAY_ARSENIC : COLOR_BLACK)
                      : (State::PartiallyChecked == state
                         ? COLOR_GRAYL : COLOR_GRAY)
                     };
        p_checkbox::drawCheckmark(chPos, chmarkClr, pMonitorDevice);
    }

    drawText(pMonitorDevice);
}

}
