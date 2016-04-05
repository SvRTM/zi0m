#ifndef TEXTCHARACTERS_H
#define TEXTCHARACTERS_H

#include "gui/kernel/additional.h"
#include "font/ifont.h"
#include "gui/io/MonitorDevice.h"
#include "gui/common.h"

#include <string>

namespace zi0m
{
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
        void setGeometry(Rect rect);
        void updateTextAbsPosition(Rect p);

        void setText(const std::u16string m_text);

        void drawText(MonitorDevice *const pMonitorDevice);
        void drawText(MonitorDevice *const pMonitorDevice, const u_color textColor,
                      const uint8_t shiftX = 0, const uint8_t shiftY = 0);

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

        void calcPxTextWidth()
        {
            pxTextWidth = 0;
            for (size_t n = 0; n < m_text.length(); ++n)
            {
                const IFont::CHAR_INFO *pDescriptor = IFont::descriptor(m_text.at(n), font());
                pxTextWidth += pDescriptor->width;
            }
        }

    protected:
        u_color m_color;
        Rect textAbsPosition;
        Alignment align;

    private:
        Rect rect;
        std::u16string m_text;
        uint16_t pxTextWidth;
};
}
#endif // TEXTCHARACTERS_H
