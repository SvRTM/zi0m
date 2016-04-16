#ifndef ABSTRACTBUTTON_H
#define ABSTRACTBUTTON_H

#include "Widget.h"
#include "AbstractTextWidget.h"

namespace zi0m
{
class AbstractButton : public AbstractTextWidget
{
    public:
        explicit AbstractButton(Point pos, Widget *const parent);
        virtual ~AbstractButton() {}

    public:
        void setAutoSize(bool autoSize);

    protected:
        void init();

    private:
        void autoSize();
        virtual const uint8_t elementWidth() const = 0;

        void p_setSize() override;
        void p_setFont() override;
        void p_setText() override;
        void p_updateAllPosition() override;

        void event(const EventType type) override;


    protected:
        static constexpr uint8_t marginLeftRight = 5;

    private:
        bool m_autoSize = true;
};
}
#endif // ABSTRACTBUTTON_H
