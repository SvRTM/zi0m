#ifndef GROUPBOXS_H
#define GROUPBOXS_H

#include "gui/widgets/Widget.h"
#include "common.h"

using namespace zi0m;

class GroupBoxs: public Widget, public Common
{
    public:
        GroupBoxs(Point pos, Size size, Widget *m_parent);
        virtual ~GroupBoxs() {}

    private:
        void paint(MonitorDevice *const pMonitorDevice) override;
        void event(const EventType type) override;

        void setupUi();
        void setFontWidgtes(std::pair<const IFont *, std::u16string> data) override;
};

#endif // GROUPBOXS_H
