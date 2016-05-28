/*
 * Copyright © 2016 Artem Smirnov
 * All right reserved.
 * Author: Artem Smirnov <msvrtm@gmail.com>
 * License: http://www.gnu.org/licenses/gpl.txt
 */

#ifndef SAMPLES_GROUPBOXS_H
#define SAMPLES_GROUPBOXS_H

#include "AbstractBody.h"

using namespace zi0m;

class GroupBoxs final : public AbstractBody
{
    public:
        GroupBoxs(Point pos, Size size, Widget *m_parent);
        virtual ~GroupBoxs() = default;

    private:
        void setFontWidgtes(std::pair<const IFont *, std::u16string> data) override;
        void setupUi();
};

#endif // SAMPLES_GROUPBOXS_H
