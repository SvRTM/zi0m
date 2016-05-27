/*
 * AnotherWindow.h
 *
 *  Created on: 14 февр. 2016 г.
 *      Author: Artem.Smirnov
 */

#ifndef BUTTONS_H_
#define BUTTONS_H_

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

#endif /* BUTTONS_H_ */
