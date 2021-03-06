/*
 * Copyright © 2016 Artem Smirnov
 * All right reserved.
 * Author: Artem Smirnov <msvrtm@gmail.com>
 * License: http://www.gnu.org/licenses/gpl.txt
 */

#include "AbstractTextWidget.h"

namespace zi0m
{

AbstractTextWidget::AbstractTextWidget(Point pos, Size size, Alignment align,
                                       Widget *const parent, const Rect &border)
    : Widget(pos, size, parent, border)
    , TextCharacters(align)
{
    typeId = TypeTag(typeId | TypeTag::ABSTRACT_TEXT_WIDGET);

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
