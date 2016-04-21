/*
 * AnotherWindow.h
 *
 *  Created on: 14 февр. 2016 г.
 *      Author: Artem.Smirnov
 */

#ifndef LABELS_H_
#define LABELS_H_

#include "gui/widgets/Widget.h"
#include "gui/widgets/Label.h"
#include "gui/text/font/ifont.h"

#include "common.h"

using namespace zi0m;

class Labels: public Widget, public Common
{
    public:
        Labels(Point pos, Size size, Widget *m_parent);
        virtual ~Labels() {}

    private:
        void paint(MonitorDevice *const pMonitorDevice) override;
        void event(const EventType type, const Point &pos) override;

        void setupUi();
        void setFontWidgtes(std::pair<const IFont *, std::u16string> data) override;

    private:
        bool isEnabledLabels;
        Label *pLblFontName;

        inline const Rect &Border() const
        {
            return zeroBorder;
        }
};

#endif /* LABELS_H_ */
