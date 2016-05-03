#include "CheckBox.h"
#include "p_checkbox.h"

namespace zi0m
{
const Rect CheckBox::border = p_checkbox::marginLeftRight + p_checkbox::boxWidth +
                              p_checkbox::marginLeftRight;

CheckBox::CheckBox(Point pos, Widget *const parent)
    : AbstractButtonASize(pos, border, parent)
{
    typeId = TypeTag(typeId | TypeTag::CHECKBOX);

    init();
}

void CheckBox::setState(State state)
{
    this->state = state;
    fullUpdate = m_refresh;
    refresh();
}

void CheckBox::setTristate(bool tristate)
{
    this->tristate = tristate;
    fullUpdate = m_refresh;
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
            fullUpdate = false;
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
            fullUpdate = false;
        }
        case EventType::TouchLeave:
            fullUpdate = false;
        default:
            boxBg = { tristate &&State::PartiallyChecked == state
                      ? COLOR_LAVENDER_BLUSH
                      : (isEnabled()
                         ? COLOR_WHITE
                         : COLOR_SILVER)
                };
    }
    if (fullUpdate)
    {
        pMonitorDevice->fillRect(screenClient(), background());
        drawText(pMonitorDevice);
    }
    else
        fullUpdate = true;

    Point chPos = {p_checkbox::marginLeftRight, int16_t((size().height - p_checkbox::boxWidth) / 2)};
    chPos.x += screenClient().x;
    chPos.y += screenClient().y;

    p_checkbox::drawCheckBox(chPos, boxBg, pMonitorDevice);

    if (State::Unchecked == state)
        return;

    u_color chmarkClr;
    chmarkClr =  {isEnabled()
                  ? (State::PartiallyChecked == state
                     ? COLOR_GRAY_ARSENIC : COLOR_BLACK)
                  : (State::PartiallyChecked == state
                     ? COLOR_GRAYL : COLOR_GRAY)
                 };
    p_checkbox::drawCheckmark(chPos, chmarkClr, pMonitorDevice);
}

}
