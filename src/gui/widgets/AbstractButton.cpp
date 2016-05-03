#include "AbstractButton.h"

namespace zi0m
{

AbstractButton::AbstractButton(Point pos, Size size, Alignment align, const Rect &border,
                               Widget *const parent)
    : AbstractTextWidget(pos, size, align, parent, border)
{
    typeId = TypeTag(typeId | TypeTag::ABSTRACT_BUTTON);
}

void AbstractButton::setCbMoved(const std::function<void (const Point &pos)> &func)
{
    cbMoved = func;
}
void AbstractButton::setCbReleased(const std::function<void ()> &func)
{
    cbReleased = func;
}
void AbstractButton::setCbPressed(const std::function<void ()> &func)
{
    cbPressed = func;
}

void AbstractButton::event(const EventType type, const Point &pos)
{
    if (!isEnabled())
        return;

    this->type = type;
    switch (type)
    {
        case EventType::TouchStart:
            if (cbPressed)
                cbPressed();
            goto L;
        case EventType::TouchEnd:
            p_cbReleased();
            if (cbReleased)
                cbReleased();
            goto L;
        case   EventType::TouchEnter:
            goto L;
        case EventType::TouchLeave:
            if (cbMoved)
                cbMoved(pos);
        L:
            refresh();
            break;
        default:
            break;
    }
}

}
