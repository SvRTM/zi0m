#ifndef COMMON_H
#define COMMON_H

#include "gui/widgets/AbstractTextWidget.h"
#include "gui/text/font/ifont.h"

#include <utility>
#include <vector>

class Common
{
    public:
        virtual void setFontWidgtes(std::pair<const IFont *, std::u16string> data) = 0;

    protected:
        std::vector<zi0m::AbstractTextWidget *> smplWidgets;
};

#endif // COMMON_H
