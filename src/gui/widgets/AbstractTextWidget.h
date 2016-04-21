#ifndef ABSTRACTTEXTWIDGET_H
#define ABSTRACTTEXTWIDGET_H

#include "Widget.h"
#include "gui/text/TextCharacters.h"

namespace zi0m
{
class AbstractTextWidget: public Widget, public TextCharacters
{
    public:
        explicit AbstractTextWidget(Point pos, Size size, Alignment align, Widget *const parent,
                                    const Rect &border = zeroBorder);
        virtual ~AbstractTextWidget() {}

    public:
        void setSize(const Size size);
        void setFont(const IFont &font);
        void setText(const std::u16string text);
        void updateAllPosition() override;

    protected:
        virtual void p_setSize() = 0;
        virtual void p_setFont() = 0;
        virtual void p_setText() = 0;
        virtual void p_updateAllPosition() = 0;
};
}
#endif // ABSTRACTTEXTWIDGET_H
