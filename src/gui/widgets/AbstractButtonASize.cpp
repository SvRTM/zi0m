#include "AbstractButtonASize.h"


namespace zi0m
{

AbstractButtonASize::AbstractButtonASize(Point pos, const Rect &border,
        Widget *const parent)
    : AbstractButton(pos, 0, Alignment(Alignment::Left | Alignment::VCenter), border, parent)
{
    typeId = TypeTag(typeId | TypeTag::ABSTRACT_BUTTON_ASIZE);

    TextCharacters::m_pos = border.x;
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
    setSize({uint16_t(pxTextWidth() + Border().x), font().height});
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
