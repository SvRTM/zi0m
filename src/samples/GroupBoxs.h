#ifndef GROUPBOXS_H
#define GROUPBOXS_H

#include "AbstractBody.h"

using namespace zi0m;

class GroupBoxs: public AbstractBody
{
    public:
        GroupBoxs(Point pos, Size size, Widget *m_parent);
        virtual ~GroupBoxs() {}

    private:
        void setFontWidgtes(std::pair<const IFont *, std::u16string> data) override;
        void setupUi();
};

#endif // GROUPBOXS_H
