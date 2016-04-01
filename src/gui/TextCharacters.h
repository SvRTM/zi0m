#ifndef TEXTCHARACTERS_H
#define TEXTCHARACTERS_H

#include "additional.h"
#include "font/ifont.h"
#include "MonitorDevice.h"
#include "common.h"

#include <string>

class TextCharacters : public virtual Additional
{
    public:
        explicit TextCharacters(Alignment align);
        virtual ~ TextCharacters() {}

    public:
        inline const std::u16string &text() const
        {
            return m_text;
        }

        void setFont(const IFont &font);

        inline const u_color color() const
        {
            return m_color;
        }
        void setColor(u_color color);

        inline Alignment alignment() const
        {
            return align;
        }
        void setAlignment(Alignment align);

    protected:
        void setText(const std::u16string m_text);
        void setAbsolutePosition(Rect absolutePosition);

        void drawText(MonitorDevice *const pMonitorDevice);
        void drawText(MonitorDevice *const pMonitorDevice, u_color textColor,
                      uint8_t shiftX = 0, uint8_t shiftY = 0);

    private:
        inline const IFont::CHAR_INFO *descriptor(const wchar_t ch,
                                                  const IFont &font) const
        {
            for (size_t n = 0; n < font.sizeOfBlock; ++n)
            {
                const IFont::BLOCK *block = &font.blocks()[n];
                if (ch >= block->startChar && ch <= block->endChar)
                    return &block->descriptors[ch - block->startChar];
            }

            const IFont::BLOCK *block = &font.blocks()[font.sizeOfBlock - 1];
            return &block->descriptors[0];
        }

        void calcPxTextWidth()
        {
            pxTextWidth = 0;
            for (size_t n = 0; n < m_text.length(); ++n)
            {
                const IFont::CHAR_INFO *pDescriptor = IFont::descriptor(m_text.at(n), font());
                pxTextWidth += pDescriptor->width;
            }
        }

    private:
        std::u16string m_text;
        uint32_t pxTextWidth;
        Rect absolutePosition;

        u_color m_color;
        Alignment align;
};

#endif // TEXTCHARACTERS_H
