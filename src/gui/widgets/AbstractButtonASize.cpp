#include "AbstractButtonASize.h"


namespace zi0m
{

AbstractButtonASize::AbstractButtonASize(Point pos, const Rect &border,
        Widget *const parent)
    : AbstractButton(pos, 0, Alignment(Alignment::Left | Alignment::VCenter), border, parent)
{
}
void AbstractButtonASize::init()
{
    autoSize();
}

void AbstractButtonASize::setAutoSize(bool autoSize)
{
    m_autoSize = autoSize;
}

void AbstractButtonASize::autoSize()
{
    if (!m_autoSize)
        return;
    Size size;
    size.width = pxTextWidth() + Border().x;
    size.height = font().height;
    setSize(size);
}

void AbstractButtonASize::p_setSize()
{
    TextCharacters::m_size = {geometry().width, geometry().height};
}
void AbstractButtonASize::p_setFont()
{
    autoSize();
}
void AbstractButtonASize::p_setText()
{
    autoSize();
}
void AbstractButtonASize::p_updateAllPosition()
{
    TextCharacters::updateAbsPosition(absoluteClientPos);
}

}
