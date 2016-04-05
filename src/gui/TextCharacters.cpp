#include "TextCharacters.h"

namespace zi0m
{

TextCharacters::TextCharacters(Alignment align) :
    m_color({COLOR_24B_BLACK}), align(align)
{
}

void TextCharacters::setText(const std::u16string text)
{
    m_text = text;
    calcPxTextWidth();
}

void TextCharacters::setFont(const IFont &font)
{
    pFont = &font;
    calcPxTextWidth();
}

void TextCharacters::setColor(u_color color)
{
    m_color = color;
}

void TextCharacters::setAlignment(Alignment align)
{
    this->align = align;
}

void TextCharacters::drawText(MonitorDevice *const pMonitorDevice)
{
    if (!isVisible())
        drawText(pMonitorDevice, {COLOR_24B_WHITE}, 1, 1);

    u_color xcolor = { isVisible() ? color().i_color : COLOR_24B_GREYD };
    drawText(pMonitorDevice, xcolor);
}

void TextCharacters::updateTextAbsPosition(Rect p)
{
    textAbsPosition = p + rect;
}

void TextCharacters::setGeometry(Rect rect)
{
    this->rect = rect;
}

void TextCharacters::drawText(MonitorDevice *const pMonitorDevice,
                              const u_color textColor, const uint8_t shiftX, const uint8_t shiftY)
{
    if (textAbsPosition.width == 0 || textAbsPosition.height == 0)
        return;

    int16_t vAlign;
    if (align & Alignment::Bottom)
        vAlign = textAbsPosition.height - font().height;
    else if (align & Alignment::VCenter)
        vAlign = (textAbsPosition.height - font().height) / 2 ;
    else // if (align & Alignment::Top)
        vAlign = 0;

    int16_t hAlign;
    if (align & Alignment::Right)
        hAlign = textAbsPosition.width - pxTextWidth;
    else if (align & Alignment::HCenter)
        hAlign = (textAbsPosition.width - pxTextWidth) / 2 ;
    else // if (align & Alignment::Left)
        hAlign = 0;


    uint8_t vAlignPos = vAlign < 0 ? abs(vAlign) : 0;
    int16_t posX = textAbsPosition.x + hAlign + shiftX;

    int16_t cx = textAbsPosition.x + textAbsPosition.width;
    int16_t cy = textAbsPosition.y + textAbsPosition.height;

    for (size_t n = 0; n < m_text.length(); ++n)
    {
        const IFont::CHAR_INFO *pDescriptor = descriptor(m_text.at(n));
        int8_t _yPos = vAlignPos - pDescriptor->fstRow;
        uint8_t yPos = _yPos < 0 ? 0 : _yPos;

        const uint8_t *pBitmaps = &font().bitmaps()[pDescriptor->position] + yPos;
        int16_t posY = textAbsPosition.y + vAlign + pDescriptor->fstRow + shiftY;

        uint16_t yMax = vAlign <= 0 ?
                        std::min(cy, int16_t(pDescriptor->sizeRow + posY))
                        : (pDescriptor->sizeRow + posY);
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
                    if ( x >= textAbsPosition.x)
                    {
                        bool px = pt >> nBit & 0x01;
                        if (!px)
                            pMonitorDevice->setPoint(x, y, textColor);
                    }
                }
                else  // IFont::Mode::Antialias
                {
                    if (x >= cx)
                    {
                        pBitmaps += pDescriptor->width - width;
                        break;
                    }

                    uint8_t pt = *(pBitmaps++);
                    if (pt != 0xFFU && x >= textAbsPosition.x)
                    {
                        u_color foreground(textColor);
                        foreground.uc_color.A = 255 - pt;
                        foreground = pMonitorDevice->alphaBlending(foreground, background());
                        pMonitorDevice->setPoint(x, y, foreground);
                    }
                }
                x++;
            }
        }
        posX += pDescriptor->width;
    }
}

}
