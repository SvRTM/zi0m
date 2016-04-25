#include "RadioButton.h"

namespace zi0m
{
const Rect RadioButton::border = AbstractButtonASize::marginLeftRight
                                 + 2 * RadioButton::radius + AbstractButtonASize::marginLeftRight;

RadioButton::RadioButton(Point pos, Widget *const parent)
    : AbstractButtonASize(pos, border, parent)
{
    init();
}

void  RadioButton::setChecked(bool checked)
{
    this->checked = checked;
    fullUpdate = m_refresh;
    refresh();
}

void RadioButton::p_cbReleased()
{
    if (!parent())
    {
        checked = !checked;
        return;
    }
    bool isEnableOtherRb = false;
    for (Widget *w : parent()->childs())
    {
        RadioButton *const rb = dynamic_cast<RadioButton *const>(w);
        if (rb == nullptr || rb == this)
            continue;
        if (rb->isChecked())
            rb->setChecked(false);
        isEnableOtherRb = true;
    }
    if (isEnableOtherRb)
    {
        if (!checked)
            setChecked(true);
    }
    else
        setChecked(!checked);
}

void RadioButton::paint(MonitorDevice *const pMonitorDevice)
{
    u_color circleBg;
    switch (type)
    {
        case EventType::TouchStart:
        case EventType::TouchEnter:
            circleBg = {COLOR_SILVER};
            fullUpdate = false;
            break;
        case EventType::TouchMove:
            return;
        case EventType::TouchEnd:
        case EventType::TouchLeave:
            fullUpdate = false;
        default:
            circleBg = {isEnabled() ? COLOR_WHITE : COLOR_SILVER};
    }
    if (fullUpdate)
    {
        pMonitorDevice->fillRect(screenClient(), background());
        drawText(pMonitorDevice);
    }
    else
        fullUpdate = true;

    Point chPos = {marginLeftRight, int16_t((size().height - 2 * radius) / 2)};
    chPos.x += screenClient().x + radius;
    chPos.y += screenClient().y + radius;

    pMonitorDevice->fillCircle(chPos.x, chPos.y, radius - 1, circleBg);

    pMonitorDevice->drawCircle(chPos.x, chPos.y, radius, chPos.y + 4, {COLOR_WHITE}, {COLOR_GRAY});
    pMonitorDevice->drawCircle(chPos.x, chPos.y, radius - 1, chPos.y + 3, {COLOR_SNOW}, {COLOR_GRAYD});

    if (checked)
        pMonitorDevice->fillCircle(chPos.x, chPos.y, radius - 4, {isEnabled() ? COLOR_BLACK : COLOR_GRAY});
}
}
