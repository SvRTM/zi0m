/*
 * Copyright © 2016 Artem Smirnov
 * All right reserved.
 * Author: Artem Smirnov <msvrtm@gmail.com>
 * License: http://www.gnu.org/licenses/gpl.txt
 */

#ifndef SAMPLES_ABSTRACTBODY_H
#define SAMPLES_ABSTRACTBODY_H

#include "gui/widgets/Widget.h"
#include "gui/widgets/AbstractTextWidget.h"
#include "gui/text/font/ifont.h"

#include <utility>
#include <vector>

using namespace zi0m;

class AbstractBody : public Widget
{
    public:
        AbstractBody(Point pos, Size size, Widget *parent) : Widget(pos, size, parent) {}
        virtual ~AbstractBody() = default;

    public:
        virtual void setFontWidgtes(std::pair<const IFont *, std::u16string> data) = 0;

    protected:
        std::vector<zi0m::AbstractTextWidget *> smplWidgets;

    private:
        void paint(MonitorDevice *const pMonitorDevice) override
        {
            pMonitorDevice->fillRect(screen(), background());
        }
        void event(const EventType type, const Point &) override
        {
            this->type = type;
        }

        inline const Rect &Border() const
        {
            return zeroBorder;
        }
};

#endif // SAMPLES_ABSTRACTBODY_H
