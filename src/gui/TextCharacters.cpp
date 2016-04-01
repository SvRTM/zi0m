#include "TextCharacters.h"

TextCharacters::TextCharacters(Alignment align): Additional(),  m_color({COLOR_24B_BLACK}),
               align(align)
{
}

void TextCharacters::setText(const std::u16string text)
{
    this->m_text = text;

    this->pxTextWidth = 0;
    for (size_t n = 0; n < text.length(); ++n)
    {
        const IFont::CHAR_INFO *pDescriptor = IFont::descriptor(text.at(n), font());
        this->pxTextWidth += pDescriptor->width;
    }
}

void TextCharacters::setAbsolutePosition(Rect absolutePosition)
{
    this->absolutePosition = absolutePosition;
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

    u_color xcolor = { isVisible() ? color().i_color : COLOR_24B_GREYD};
    drawText(pMonitorDevice, xcolor);
}

void TextCharacters::drawText(MonitorDevice *const pMonitorDevice,
                              u_color textColor, uint8_t shiftX, uint8_t shiftY)
{
    if (absolutePosition.width == 0 || absolutePosition.height == 0)
        return;

    int16_t vAlign = 0;
    if (align & Alignment::Bottom)
        vAlign = absolutePosition.height - font().height;
    else if (align & Alignment::VCenter)
        vAlign = (absolutePosition.height - font().height) / 2 ;
    //    else if (align & Alignment::Top)
    //        vAlign = 0;

    int16_t hAlign = 0;
    if (align & Alignment::Right)
        hAlign = absolutePosition.width - pxTextWidth;
    else if (align & Alignment::HCenter)
        hAlign = (absolutePosition.width - pxTextWidth) / 2 ;
    //    else if (align & Alignment::Left)
    //        hAlign = 0;


    int16_t vAlignPos = vAlign < 0 ? abs(vAlign) : 0;
    int16_t posX = absolutePosition.x + hAlign + shiftX;

    for (size_t n = 0; n < m_text.length(); ++n)
    {
        const IFont::CHAR_INFO *pDescriptor = descriptor(m_text.at(n), font());
        int8_t yPos = vAlignPos - pDescriptor->fstRow;
        yPos = yPos < 0 ? 0 : yPos;

        const uint8_t *pBitmaps = &font().bitmaps()[pDescriptor->position] + yPos;
        int16_t posY = absolutePosition.y + vAlign + pDescriptor->fstRow + shiftY;

        uint16_t yMax = vAlign <= 0 ?
                        std::min(absolutePosition.height + absolutePosition.y,
                                 pDescriptor->sizeRow + posY)
                        : (pDescriptor->sizeRow + posY);
        for (uint8_t y = posY + yPos; y < yMax; ++y)
        {
            uint8_t pt = 0;
            int16_t x = posX;
            for (uint8_t width = 0; width < pDescriptor->width; ++width)
            {
                if (x >= absolutePosition.x + absolutePosition.width)
                    break;

                if (IFont::Mode::Bitmap ==  font().mode)
                {
                    const uint8_t nBit = 7 - (width % 8);
                    if (nBit == 7)
                        pt = *(pBitmaps++);
                    if ( x >= absolutePosition.x)
                    {
                        bool px = pt >> nBit & 0x01;
                        if (!px)
                            pMonitorDevice->setPoint(x, y, textColor);
                    }
                }
                else  // IFont::Mode::Antialias
                {
                    uint8_t pt = *(pBitmaps++);
                    if (pt != 0xFFU && x >= absolutePosition.x)
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
