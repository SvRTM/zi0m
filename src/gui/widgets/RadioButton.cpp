#include "RadioButton.h"

namespace zi0m
{
const Rect RadioButton::border = AbstractButton::marginLeftRight + 2 * RadioButton::radius
                                 + AbstractButton::marginLeftRight;

RadioButton::RadioButton(Point pos, Widget *const parent)
    : AbstractButton(pos, border, parent)
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
    pMonitorDevice->fillRect(screenClient(), background());

    Point chPos = {marginLeftRight, int16_t((size().height - 2 * radius) / 2)};
    chPos.x += screenClient().x + radius;
    chPos.y += screenClient().y + radius;

    pMonitorDevice->fillCircle(chPos.x, chPos.y, radius - 1, circleBg);

    pMonitorDevice->drawCircle(chPos.x, chPos.y, radius, chPos.y + 4, {COLOR_WHITE}, {COLOR_GRAY});
    pMonitorDevice->drawCircle(chPos.x, chPos.y, radius - 1, chPos.y + 3, {COLOR_SNOW}, {COLOR_GRAYD});

    if (checked)
        pMonitorDevice->fillCircle(chPos.x, chPos.y, radius - 4, {isEnabled() ? COLOR_BLACK : COLOR_GRAY});

    drawText(pMonitorDevice);
}
}
