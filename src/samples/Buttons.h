/*
 * AnotherWindow.h
 *
 *  Created on: 14 февр. 2016 г.
 *      Author: Artem.Smirnov
 */

#ifndef BUTTONS_H_
#define BUTTONS_H_

#include "gui/widgets/Widget.h"

#include "common.h"

using namespace zi0m;

class Buttons: public Widget, public Common
{
    public:
        Buttons(Point pos, Size size, Widget *m_parent);
        virtual ~Buttons() {}

    private:
        void paint(MonitorDevice *const pMonitorDevice) override;
        void event(const EventType type, const Point &pos) override;

        void setupUi();
        void setFontWidgtes(std::pair<const IFont *, std::u16string> data) override;

        inline const Rect &Border() const
        {
            return zeroBorder;
        }
};

#endif /* BUTTONS_H_ */
