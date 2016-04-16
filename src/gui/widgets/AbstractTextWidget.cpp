#include "AbstractTextWidget.h"

namespace zi0m
{

AbstractTextWidget::AbstractTextWidget(Point pos, Size size, Alignment align,
                                       Widget *const parent)
    : Widget(pos, size, parent)
    , TextCharacters(align)
{
    if (parent)
        setBackground(parent->background());
}

void AbstractTextWidget::setSize(const Size size)
{
    Widget::setSize(size);
    p_setSize();
}

void AbstractTextWidget::setFont(const IFont &font)
{
    TextCharacters::setFont(font);
    p_setFont();
}

void AbstractTextWidget::setText(const std::u16string text)
{
    TextCharacters::setText(text);
    p_setText();
}

void AbstractTextWidget::updateAllPosition()
{
    Widget::updateAllPosition();
    p_updateAllPosition();
}

}
