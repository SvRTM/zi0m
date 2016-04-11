/*
 * Label.h
 *
 *  Created on: 6 марта 2016 г.
 *      Author: Artem.Smirnov
 */

#ifndef LABEL_H_
#define LABEL_H_

#include "Widget.h"
#include "gui/text/TextCharacters.h"

#include <string>

namespace zi0m
{
class Label: public Widget, public TextCharacters
{
    public:
        explicit Label(Point pos, Size size, Widget *const parent, Alignment
                       align = Alignment(Alignment::VCenter | Alignment::Left));
        virtual ~Label() {}

    public:
        void setSize(Size size);

    private:
        void updateAllPosition() override;
        void event(EventType type) override;
        void paint(MonitorDevice *const pMonitorDevice) override;
};
}
#endif /* LABEL_H_ */
