#ifndef TEXTCHARACTERS_H
#define TEXTCHARACTERS_H

#include "gui/kernel/additional.h"
#include "font/ifont.h"
#include "gui/io/MonitorDevice.h"
#include "gui/common.h"

#include <string>

namespace zi0m
{
class TextCharacters: public virtual Additional
{
    public:
        explicit TextCharacters(Alignment align);
        virtual ~TextCharacters() {}

    public:
        inline const std::u16string &text() const
        {
            return m_text;
        }
        void setText(const std::u16string m_text);
        uint16_t pxTextWidth() const
        {
            return m_pxTextWidth;
        }

        void setFont(const IFont &font);

        inline const u_color color() const
        {
            return m_color;
        }
        void setColor(const u_color color);

        inline Alignment alignment() const
        {
            return align;
        }
        void setAlignment(Alignment align);

    protected:
        void updateAbsPosition(const Point &pos);

        void drawText(MonitorDevice *const pMonitorDevice, const int16_t horizontalShift = 0);
        void drawText(MonitorDevice *const pMonitorDevice, const u_color textColor,
                      const uint8_t shiftX, const uint8_t shiftY, const int16_t horizontalShift = 0);

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
            m_pxTextWidth = 0;
            for (size_t n = 0; n < m_text.length(); ++n)
            {
                const IFont::CHAR_INFO *pDescriptor = IFont::descriptor(m_text.at(n), font());
                m_pxTextWidth += pDescriptor->width;
            }
        }


    protected:
        Point m_pos;
        Size m_size;
        Alignment align;
        u_color m_color = {COLOR_BLACK};

    private:
        Point new_textAbsPosition;

        std::u16string m_text;
        uint16_t m_pxTextWidth = 0;
};
}
#endif // TEXTCHARACTERS_H
