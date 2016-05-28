/*
 * Copyright © 2016 Artem Smirnov
 * All right reserved.
 * Author: Artem Smirnov <msvrtm@gmail.com>
 * License: http://www.gnu.org/licenses/gpl.txt
 */

#ifndef SAMPLES_LABELS_H_
#define SAMPLES_LABELS_H_

#include "gui/widgets/Label.h"
#include "gui/text/font/ifont.h"

#include "AbstractBody.h"

using namespace zi0m;

class Labels final : public AbstractBody
{
    public:
        Labels(Point pos, Size size, Widget *m_parent);
        virtual ~Labels() = default;
    private:
        Labels(const Labels &) = delete;
        Labels &operator=(const Labels &) = delete;

    private:
        void setFontWidgtes(std::pair<const IFont *, std::u16string> data) override;
        void setupUi();

    private:
        bool isEnabledLabels;
        Label *pLblFontName = nullptr;
};

#endif /* SAMPLES_LABELS_H_ */
