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
#include <math.h>
class Label: public Widget
{
    public:
        explicit Label(Widget *parent,
                       Alignment _align = (Alignment) (Alignment::VCenter | Alignment::Left));
        virtual ~Label();

    public:
        void setText(const std::u16string text);

        inline Alignment alignment() const
        {
            return align;
        }
        void setAlignment(Alignment align);

        inline const u_color color() const
        {
            return m_color;
        }
        void setColor(u_color color);

        void paint(MonitorDevice *const pMonitorDevice) override;

    private:
        inline const IFont::CHAR_INFO *descriptor(const wchar_t ch) const
        {
            for (size_t n = 0; n < font().sizeOfBlock; ++n)
            {
                const IFont::BLOCK *block = &font().blocks()[n];
                if (ch >= block->startChar && ch <= block->endChar)
                    return &block->descriptors[ch - block->startChar];
            }

            const IFont::BLOCK *block = &font().blocks()[font().sizeOfBlock - 1];
            return &block->descriptors[0];
        }

        const uint16_t textWidth() const;

        void drawText(MonitorDevice *const pMonitorDevice, const u_color pxColor,
                      const Alignment align);

    private:
        Alignment align;
        std::u16string m_text;
        u_color m_color;
        uint32_t m_textWidth;
};

#endif /* SRC_GUI_LABEL_H_ */
