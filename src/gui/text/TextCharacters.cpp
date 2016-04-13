#include "TextCharacters.h"

namespace zi0m
{

TextCharacters::TextCharacters(Alignment align) : align(align)
{
}
TextCharacters::TextCharacters(Point pos, Size size, Alignment align) :
    m_pos(pos), m_size(size), align(align)
{
}

void TextCharacters::setText(const std::u16string text)
{
    m_text = text;
    calcPxTextWidth();
    refresh();
}

void TextCharacters::setFont(const IFont &font)
{
    pFont = &font;
    calcPxTextWidth();
    refresh();
}

void TextCharacters::setColor(u_color color)
{
    m_color = color;
    refresh();
}

void TextCharacters::setAlignment(Alignment align)
{
    this->align = align;
    refresh();
}

void TextCharacters::drawText(MonitorDevice *const pMonitorDevice)
{
    if (!isEnabled())
        drawText(pMonitorDevice, {COLOR_WHITE}, 1, 1);

    u_color xcolor = { isEnabled() ? color().value : COLOR_GRAY };
    drawText(pMonitorDevice, xcolor);
}

void TextCharacters::setSize(Size size)
{
    m_size  = size;
}

void TextCharacters::updateAbsPosition(Point pos)
{
    new_textAbsPosition = m_pos + pos;
}

void TextCharacters::drawText(MonitorDevice *const pMonitorDevice,
                              const u_color textColor, const uint8_t shiftX, const uint8_t shiftY)
{
    if (m_size.width == 0 || m_size.height == 0)
        return;

    int16_t vAlign;
    if (align & Alignment::Bottom)
        vAlign = m_size.height - font().height;
    else if (align & Alignment::VCenter)
        vAlign = (m_size.height - font().height) / 2 ;
    else // if (align & Alignment::Top)
        vAlign = 0;

    int16_t hAlign;
    if (align & Alignment::Right)
        hAlign = m_size.width - m_pxTextWidth;
    else if (align & Alignment::HCenter)
        hAlign = (m_size.width - m_pxTextWidth) / 2 ;
    else // if (align & Alignment::Left)
        hAlign = 0;


    const uint8_t vAlignPos = vAlign < 0 ? abs(vAlign) : 0;
    int16_t posX = new_textAbsPosition.x + hAlign + shiftX;

    const int16_t cx = new_textAbsPosition.x + m_size.width;
    const int16_t cy = new_textAbsPosition.y + m_size.height;

    for (size_t n = 0; n < m_text.length(); ++n)
    {
        const IFont::CHAR_INFO *pDescriptor = descriptor(m_text.at(n));
        const int8_t _yPos = vAlignPos - pDescriptor->fstRow;
        const uint8_t yPos = _yPos < 0 ? 0 : _yPos;

        const uint8_t *pBitmaps = &font().bitmaps()[pDescriptor->position + yPos *
                                  (IFont::Mode::Bitmap == font().mode ? pDescriptor->width / 8 : pDescriptor->width)];
        const int16_t posY = new_textAbsPosition.y + vAlign + pDescriptor->fstRow + shiftY;

        const int16_t yMax = std::min(cy, int16_t(pDescriptor->sizeRow + posY));
        for (uint16_t y = posY + yPos; y < yMax; ++y)
        {
            uint8_t pt = 0;
            int16_t x = posX;
            for (uint8_t width = 0; width < pDescriptor->width; ++width)
            {
                if (IFont::Mode::Bitmap ==  font().mode)
                {
                    if (x >= cx)
                    {
                        pBitmaps += (pDescriptor->width - width) / 8;
                        break;
                    }

                    const uint8_t nBit = 7 - (width % 8);
                    if (nBit == 7)
                        pt = *(pBitmaps++);
                    if ( x >= new_textAbsPosition.x)
                    {
                        const bool px = pt >> nBit & 0x01;
                        if (!px)
                            pMonitorDevice->drawPoint(x, y, textColor);
                    }
                }
                else  // IFont::Mode::Antialias
                {
                    if (x >= cx)
                    {
                        pBitmaps += pDescriptor->width - width;
                        break;
                    }

                    const uint8_t pt = *(pBitmaps++);
                    if (pt != 0xFFU && x >= new_textAbsPosition.x)
                    {
                        u_color foreground(textColor);
#ifdef RGB888
                        foreground.argb.A = 255 - pt;
                        foreground = pMonitorDevice->alphaBlending(foreground, background());
#elif  RGB565
                        foreground = pMonitorDevice->alphaBlending(foreground, background(), 255 - pt);
#endif
                        pMonitorDevice->drawPoint(x, y, foreground);
                    }
                }
                x++;
            }
        }
        posX += pDescriptor->width;
    }
}

}
