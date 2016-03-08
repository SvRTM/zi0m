/*
 * Label.h
 *
 *  Created on: 6 марта 2016 г.
 *      Author: Artem.Smirnov
 */

#ifndef SRC_GUI_LABEL_H_
#define SRC_GUI_LABEL_H_

#include "Widget.h"

#include <string>

class Label: public Widget
{
    public:
        Label(Widget *parent);
        virtual ~Label();

        void setText(const std::u16string &str);

        void paint(MonitorDevice * const pMonitorDevice) override;

    private:
        const ONE_BIT_COLOR::CHAR_INFO *descriptor(const wchar_t ch) const
        {
            for (size_t n = 0;
                    n < sizeof(font->blocks) / sizeof(font->blocks[0]); ++n)
            {
                const ONE_BIT_COLOR::BLOCK *block = &font->blocks[n];
                if (ch >= block->startChar && ch <= block->endChar)
                    return &block->descriptors[ch - block->startChar];
            }

            return nullptr;
        }

    private:
        const std::u16string *m_pText;

};

#endif /* SRC_GUI_LABEL_H_ */
