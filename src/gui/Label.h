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
#include <iostream>

class Label: public Widget
{
    public:
        Label(Widget *parent,
                uint8_t align = Alignment::VCenter | Alignment::Left);
        virtual ~Label();

        void setText(const std::u16string str);

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

            const ONE_BIT_COLOR::BLOCK *block =
                    &font->blocks[sizeof(font->blocks) / sizeof(font->blocks[0])
                            - 1];
            return &block->descriptors[0];
        }

        uint16_t textWidth()
        {
            uint16_t width = 0;
            for (size_t i = 0; i < m_pText.length(); i++)
            {
                const ONE_BIT_COLOR::CHAR_INFO *pDescriptor = descriptor(
                        m_pText.at(i));
                width += pDescriptor->width;
            }
            return width;
        }

    private:
        uint8_t align;
        std::u16string m_pText;
        uint32_t m_textWidth;
};

#endif /* SRC_GUI_LABEL_H_ */
