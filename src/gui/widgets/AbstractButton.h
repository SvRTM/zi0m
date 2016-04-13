#ifndef ABSTRACTBUTTON_H
#define ABSTRACTBUTTON_H

#include "Widget.h"
#include "gui/text/TextCharacters.h"

namespace zi0m
{
class AbstractButton : public Widget, public TextCharacters
{
    public:
        explicit AbstractButton(Point pos, Widget *const parent);
        virtual ~AbstractButton() {}

    public:
        void setAutoSize(bool autoSize);
        void setSize(Size size);
        void setFont(const IFont &font);
        void setText(const std::u16string text);

    protected:
        void init();

    private:
        virtual const uint8_t elementWidth() const = 0;
        void event(EventType type) override;
        void updateAllPosition() override;
        void autoSize();


    protected:
        const uint8_t marginLeftRight = 5;

    private:
        bool m_autoSize = true;
};
}
#endif // ABSTRACTBUTTON_H
