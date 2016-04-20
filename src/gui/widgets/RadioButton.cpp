#include "RadioButton.h"

namespace zi0m
{

RadioButton::RadioButton(Point pos, Widget *const parent)
    : AbstractButton(pos, parent)
{
    init();
}

void  RadioButton::setChecked(bool checked)
{
    this->checked = checked;
    refresh();
}

void RadioButton::paint(MonitorDevice *const pMonitorDevice)
{
    u_color circleBg;
    switch (type)
    {
        case EventType::TouchStart:
        case EventType::TouchEnter:
            circleBg = {COLOR_SILVER};
            break;
        case EventType::TouchMove:
            return;
        case EventType::TouchEnd:
        default:
            circleBg = {isEnabled() ? COLOR_WHITE : COLOR_SILVER};
    }
    pMonitorDevice->fillRect(screen(), background());

    Point chPos = {marginLeftRight, int16_t((size().height - elementWidth()) / 2)};
    chPos.x += screen().x + radius;
    chPos.y += screen().y + radius;

    pMonitorDevice->fillCircle(chPos.x, chPos.y, radius - 1, circleBg);

    pMonitorDevice->circle(chPos.x, chPos.y, radius, chPos.y + 4, {COLOR_WHITE}, {COLOR_GRAY});
    pMonitorDevice->circle(chPos.x, chPos.y, radius - 1, chPos.y + 3, {COLOR_SNOW}, {COLOR_GRAYD});

    if (checked)
        pMonitorDevice->fillCircle(chPos.x, chPos.y, radius - 4, {isEnabled() ? COLOR_BLACK : COLOR_GRAY});

    drawText(pMonitorDevice);
}

const uint8_t RadioButton::elementWidth() const
{
    return 2 * radius;
}
}
