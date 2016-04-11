#include "CheckBox.h"

namespace zi0m
{

constexpr uint8_t CheckBox::checkmark[8];

CheckBox::CheckBox(Point pos, Widget *const parent)
    : Widget(pos, {uint16_t(marginLeftRight + boxWidth), uint16_t(marginLeftRight + boxWidth)},
parent)
, TextCharacters(Alignment(Alignment::Left | Alignment::VCenter))
{
    if (parent)
        setBackground(parent->background());

    TextCharacters::m_pos = {int16_t(marginLeftRight + boxWidth + marginLeftRight), 0};
    autoSize();
}

void CheckBox::setAutoSize(bool autoSize)
{
    m_autoSize = autoSize;
}

void CheckBox::setSize(Size size)
{
    TextCharacters::setSize({uint16_t(size.width - marginLeftRight + boxWidth + marginLeftRight),
                             size.height
                            });
    Widget::setSize(size);
}

void CheckBox::setFont(const IFont &font)
{
    TextCharacters::setFont(font);
    autoSize();
}

void CheckBox::setText(const std::u16string text)
{
    TextCharacters::setText(text);
    autoSize();
}

void CheckBox::autoSize()
{
    if (!m_autoSize)
        return;
    Size size;
    size.width = pxTextWidth() + marginLeftRight + boxWidth + marginLeftRight;
    size.height = font().height;
    setSize(size);
}

void CheckBox::updateAllPosition()
{
    Widget::updateAllPosition();
    TextCharacters::updateAbsPosition(absolutePos);
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

void CheckBox::event(EventType type)
{
    if (!isEnabled())
        return;

    this->type = type;
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

    Point chPos = {marginLeftRight, int16_t((size().height - boxWidth) / 2)};
    chPos.x += screen().x;
    chPos.y += screen().y;
    pMonitorDevice->fillRect({int16_t(chPos.x + 2 * borderWidth), int16_t(chPos.y + 2 * borderWidth),
                              uint16_t(boxWidth - 4 * borderWidth), uint16_t(boxWidth - 4 * borderWidth)
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

    u_color colorTL2({COLOR_GRAYD});
    // left
    pMonitorDevice->fillRect({int16_t(chPos.x + borderWidth), int16_t(chPos.y + borderWidth),
                              borderWidth, uint16_t(boxWidth  - 3 * borderWidth)
                             }, colorTL2);
    // top
    pMonitorDevice->fillRect({int16_t(chPos.x + 2 * borderWidth), int16_t(chPos.y + borderWidth),
                              uint16_t(boxWidth - 4 * borderWidth), borderWidth
                             }, colorTL2);


    u_color colorBR2 = {COLOR_SILVER};
    // bottom
    pMonitorDevice->fillRect({int16_t(chPos.x + borderWidth), int16_t(chPos.y + boxWidth - 2 * borderWidth),
                              uint16_t(boxWidth - 3 * borderWidth), borderWidth
                             }, colorBR2);
    // right
    pMonitorDevice->fillRect({int16_t(chPos.x + boxWidth - 2 * borderWidth), int16_t(chPos.y + borderWidth),
                              borderWidth, uint16_t(boxWidth - 2 * borderWidth)
                             }, colorBR2);

    u_color colorBR = {COLOR_WHITE};
    // bottom
    pMonitorDevice->fillRect({chPos.x, int16_t(chPos.y + boxWidth - borderWidth),
                              uint16_t(boxWidth - borderWidth), borderWidth
                             }, colorBR);
    // right
    pMonitorDevice->fillRect({int16_t(chPos.x + boxWidth - borderWidth), chPos.y,
                              borderWidth, boxWidth
                             }, colorBR);

    u_color colorTL = {COLOR_GRAY};
    // left
    pMonitorDevice->fillRect({chPos.x, chPos.y, borderWidth, uint16_t(boxWidth - borderWidth)
                             }, colorTL);
    // top
    pMonitorDevice->fillRect({chPos.x, chPos.y, uint16_t(boxWidth - borderWidth), borderWidth
                             }, colorTL);

    drawText(pMonitorDevice);
}

}
