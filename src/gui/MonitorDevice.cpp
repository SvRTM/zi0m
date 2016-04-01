/*
 * MonitorDevice.cpp
 *
 *  Created on: 3 февр. 2016 г.
 *      Author: Artem.Smirnov
 */

#include "MonitorDevice.h"

MonitorDevice::MonitorDevice()
{
}
MonitorDevice::~MonitorDevice()
{
}


void MonitorDevice::drawText(const std::u16string &text, Rect &screenRect,
                             const IFont &font, const u_color textColor, const u_color bgColor,
                             const Alignment align, uint32_t pxTextWidth, uint8_t shiftX, uint8_t shiftY)
{
    int16_t vAlign = 0;
    if (align & Alignment::Bottom)
        vAlign = screenRect.height - font.height;
    else if (align & Alignment::VCenter)
        vAlign = (screenRect.height - font.height) / 2 ;
    //    else if (align & Alignment::Top)
    //        vAlign = 0;

    int16_t hAlign = 0;
    if (align & Alignment::Right)
        hAlign = screenRect.width - pxTextWidth;
    else if (align & Alignment::HCenter)
        hAlign = (screenRect.width - pxTextWidth) / 2 ;
    //    else if (align & Alignment::Left)
    //        hAlign = 0;


    int16_t vAlignPos = vAlign < 0 ? abs(vAlign) : 0;
    int16_t posX = screenRect.x + hAlign + shiftX;

    for (size_t n = 0; n < text.length(); ++n)
    {
        const IFont::CHAR_INFO *pDescriptor = descriptor(text.at(n), font);
        int8_t yPos = vAlignPos - pDescriptor->fstRow;
        yPos = yPos < 0 ? 0 : yPos;

        const uint8_t *pBitmaps = &font.bitmaps()[pDescriptor->position] + yPos;
        int16_t posY = screenRect.y + vAlign + pDescriptor->fstRow;

        uint16_t yMax = vAlign <= 0 ?
                        std::min(screenRect.height + screenRect.y, pDescriptor->sizeRow + posY + shiftY)
                        : (pDescriptor->sizeRow + posY);
        for (uint8_t y = posY + yPos + shiftY; y <  yMax; ++y)
        {
            uint8_t pt = 0;
            int16_t x = posX;
            for (uint8_t width = 0; width < pDescriptor->width; ++width)
            {
                if (x >= screenRect.x + screenRect.width)
                    break;

                if (IFont::Mode::Bitmap ==  font.mode)
                {
                    const uint8_t nBit = 7 - (width % 8);
                    if (nBit == 7)
                        pt = *(pBitmaps++);
                    if ( x >= screenRect.x)
                    {
                        bool px = pt >> nBit & 0x01;
                        if (!px)
                            setPoint(x, y, textColor);
                    }
                }
                else  // IFont::Mode::Antialias
                {
                    uint8_t pt = *(pBitmaps++);
                    if (pt != 0xFFU && x >= screenRect.x)
                    {
                        u_color foreground(textColor);
                        foreground.uc_color.A = 255 - pt;
                        foreground = alphaBlending(foreground, bgColor);
                        setPoint(x, y, foreground);
                    }
                }
                x++;
            }
        }
        posX += pDescriptor->width;
    }
}
