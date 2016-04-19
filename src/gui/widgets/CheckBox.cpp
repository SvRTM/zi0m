#include "CheckBox.h"

namespace zi0m
{

constexpr uint8_t CheckBox::checkmark[8];

CheckBox::CheckBox(Point pos, Widget *const parent)
    : AbstractButton(pos, parent)
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
    switch (eventType())
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
    pMonitorDevice->fillRect(screen(), background());

    Point chPos = {marginLeftRight, int16_t((size().height - elementWidth()) / 2)};
    chPos.x += screen().x;
    chPos.y += screen().y;
    pMonitorDevice->fillRect({int16_t(chPos.x + 2 * borderWidth), int16_t(chPos.y + 2 * borderWidth),
                              uint16_t(elementWidth() - 4 * borderWidth), uint16_t(elementWidth() - 4 * borderWidth)
                             }, boxBg);

    if (State::Unchecked != state)
    {
        u_color chmarkClr;
        chmarkClr =  {isEnabled()
                      ? (State::PartiallyChecked == state
                         ? COLOR_GRAY_ARSENIC : COLOR_BLACK)
                      : (State::PartiallyChecked == state
                         ? COLOR_GRAYL : COLOR_GRAY)
                     };
        drawCheckmark(chPos, chmarkClr, pMonitorDevice );
    }

    u_color colorTL = {COLOR_GRAY};
    // left
    pMonitorDevice->fillRect({chPos.x, chPos.y, borderWidth, uint16_t(elementWidth() - borderWidth)
                             }, colorTL);
    // top
    pMonitorDevice->fillRect({chPos.x, chPos.y, uint16_t(elementWidth() - borderWidth), borderWidth
                             }, colorTL);

    u_color colorTL2({COLOR_GRAYD});
    // left
    pMonitorDevice->fillRect({int16_t(chPos.x + borderWidth), int16_t(chPos.y + borderWidth),
                              borderWidth, uint16_t(elementWidth()  - 3 * borderWidth)
                             }, colorTL2);
    // top
    pMonitorDevice->fillRect({int16_t(chPos.x + 2 * borderWidth), int16_t(chPos.y + borderWidth),
                              uint16_t(elementWidth() - 4 * borderWidth), borderWidth
                             }, colorTL2);


    u_color colorBR2 = {COLOR_SILVER};
    // bottom
    pMonitorDevice->fillRect({int16_t(chPos.x + borderWidth), int16_t(chPos.y + elementWidth() - 2 * borderWidth),
                              uint16_t(elementWidth() - 3 * borderWidth), borderWidth
                             }, colorBR2);
    // right
    pMonitorDevice->fillRect({int16_t(chPos.x + elementWidth() - 2 * borderWidth), int16_t(chPos.y + borderWidth),
                              borderWidth, uint16_t(elementWidth() - 2 * borderWidth)
                             }, colorBR2);

    u_color colorBR = {COLOR_WHITE};
    // bottom
    pMonitorDevice->fillRect({chPos.x, int16_t(chPos.y + elementWidth() - borderWidth),
                              uint16_t(elementWidth() - borderWidth), borderWidth
                             }, colorBR);
    // right
    pMonitorDevice->fillRect({int16_t(chPos.x + elementWidth() - borderWidth), chPos.y,
                              borderWidth, elementWidth()
                             }, colorBR);

    drawText(pMonitorDevice);
}

const uint8_t CheckBox::elementWidth() const
{
    return boxWidth;
}

}
