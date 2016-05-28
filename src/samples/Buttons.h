/*
 * Copyright © 2016 Artem Smirnov
 * All right reserved.
 * Author: Artem Smirnov <msvrtm@gmail.com>
 * License: http://www.gnu.org/licenses/gpl.txt
 */

#ifndef SAMPLES_BUTTONS_H_
#define SAMPLES_BUTTONS_H_

#include "AbstractBody.h"

using namespace zi0m;

class Buttons final : public AbstractBody
{
    public:
        Buttons(Point pos, Size size, Widget *m_parent);
        virtual ~Buttons() = default;

    private:
        void setFontWidgtes(std::pair<const IFont *, std::u16string> data) override;
        void setupUi();
};

#endif /* SAMPLES_BUTTONS_H_ */
