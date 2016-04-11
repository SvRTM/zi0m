#ifndef COMMON_H
#define COMMON_H

#include "gui/text/TextCharacters.h"
#include "gui/text/font/ifont.h"

#include <utility>
#include <string>
#include <vector>

class Common
{
    public:
        virtual void setFontWidgtes(std::pair<const IFont *, std::u16string> data) = 0;

    protected:
        std::vector<zi0m::TextCharacters *> smplWidgets;
};

#endif // COMMON_H
