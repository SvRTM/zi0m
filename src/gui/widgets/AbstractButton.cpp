#include "AbstractButton.h"

namespace zi0m
{

AbstractButton::AbstractButton(Point pos, const Rect &border, Widget *const parent)
    : AbstractTextWidget(pos, 0, Alignment(Alignment::Left | Alignment::VCenter), parent,
                         border)
{
    TextCharacters::m_pos = border.x;
}
void AbstractButton::init()
{
    autoSize();
}

void AbstractButton::setAutoSize(bool autoSize)
{
    m_autoSize = autoSize;
}

void AbstractButton::autoSize()
{
    if (!m_autoSize)
        return;
    Size size;
    size.width = pxTextWidth() + Border().x;
    size.height = font().height;
    setSize(size);
}

void AbstractButton::p_setSize()
{
    TextCharacters::m_size = {geometry().width, geometry().height};
}
void AbstractButton::p_setFont()
{
    autoSize();
}
void AbstractButton::p_setText()
{
    autoSize();
}
void AbstractButton::p_updateAllPosition()
{
    TextCharacters::updateAbsPosition(absoluteClientPos);
}

void AbstractButton::event(const EventType type, const Point &pos)
{
    if (!isEnabled())
        return;

    this->type = type;
    refresh();
}

}
