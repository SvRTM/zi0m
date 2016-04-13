#include "AbstractButton.h"

namespace zi0m
{

AbstractButton::AbstractButton(Point pos, Widget *const parent)
    : Widget(pos, 0, parent)
    , TextCharacters(Alignment(Alignment::Left | Alignment::VCenter))
{
    if (parent)
        setBackground(parent->background());
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

void AbstractButton::setSize(Size size)
{
    TextCharacters::setSize({uint16_t(size.width - marginLeftRight + elementWidth() + marginLeftRight),
                             size.height
                            });
    Widget::setSize(size);
}

void AbstractButton::setFont(const IFont &font)
{
    TextCharacters::setFont(font);
    autoSize();
}

void AbstractButton::setText(const std::u16string text)
{
    TextCharacters::setText(text);
    autoSize();
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

void AbstractButton::updateAllPosition()
{
    Widget::updateAllPosition();
    TextCharacters::updateAbsPosition(absolutePos);
}

void AbstractButton::event(EventType type)
{
    if (!isEnabled())
        return;

    this->type = type;
    refresh();
}

}
