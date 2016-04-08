/*
 * AnotherWindow.h
 *
 *  Created on: 14 февр. 2016 г.
 *      Author: Artem.Smirnov
 */

#ifndef GUI_AnotherWindow_H_
#define GUI_AnotherWindow_H_

#include "gui/widgets/Widget.h"
#include "gui/widgets/Label.h"
#include "gui/text/font/ifont.h"

#include <vector>

using namespace zi0m;

class Labels: public Widget
{
    public:
        Labels(Point pos, Size size, Widget *parent);
        virtual ~Labels() {}

    private:
        void paint(MonitorDevice *const pMonitorDevice) override;
        void event(EventType type) override;

        void setupUi();

    private:
        bool isEnabledLabels;
        std::vector<Label *> labels;
        uint8_t nFont;
        std::vector<std::pair<const IFont *, std::u16string>> fonts;
        Label *lblFontName;
};

#endif /* GUI_AnotherWindow_H_ */
