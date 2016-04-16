#include "AbstractButton.h"

namespace zi0m
{

AbstractButton::AbstractButton(Point pos, Widget *const parent)
    : AbstractTextWidget(pos, 0, Alignment(Alignment::Left | Alignment::VCenter), parent)
{
}
void AbstractButton::init()
{
    setSize(marginLeftRight + elementWidth());
    TextCharacters::m_pos = marginLeftRight + elementWidth() + marginLeftRight;
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
    size.width = pxTextWidth() + marginLeftRight + elementWidth() + marginLeftRight;
    size.height = font().height;
    setSize(size);
}

void AbstractButton::p_setSize()
{
    TextCharacters::m_size = {uint16_t(size().width - marginLeftRight + elementWidth() + marginLeftRight),
                              size().height
                             };
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
    TextCharacters::updateAbsPosition(absolutePos);
}

void AbstractButton::event(const EventType type)
{
    if (!isEnabled())
        return;

    this->type = type;
    refresh();
}

}
