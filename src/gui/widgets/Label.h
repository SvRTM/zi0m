/*
 * Label.h
 *
 *  Created on: 6 марта 2016 г.
 *      Author: Artem.Smirnov
 */

#ifndef LABEL_H_
#define LABEL_H_

#include "Widget.h"
#include "AbstractTextWidget.h"

namespace zi0m
{
class Label: public AbstractTextWidget
{
    public:
        explicit Label(Point pos, Size size, Widget *const parent, Alignment
                       align = Alignment(Alignment::VCenter | Alignment::Left));
        virtual ~Label() = default;

    private:
        void p_setSize() override;
        void p_setFont() override {}
        void p_setText() override {}
        void p_updateAllPosition() override;

        void event(const EventType type, const Point &) override
        {
            this->type = type;
        }
        void paint(MonitorDevice *const pMonitorDevice) override;

        inline const Rect &Border() const
        {
            return zeroBorder;
        }
};
}
#endif /* LABEL_H_ */
