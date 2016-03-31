/*
 * Label.cpp
 *
 *  Created on: 6 марта 2016 г.
 *      Author: Artem.Smirnov
 */

#include "Label.h"

Label::Label(Widget *parent, Alignment _align)
    : Widget(parent), align(_align), m_color({COLOR_24B_BLACK}), m_textWidth(0)
{
}
Label::~Label()
{
}

const uint16_t Label::textWidth() const
{
    uint16_t width = 0;
    for (size_t n = 0; n < m_text.length(); ++n)
    {
        const IFont::CHAR_INFO *pDescriptor = descriptor(m_text.at(n));
        width += pDescriptor->width;
    }
    return width;
}

void Label::setText(const std::u16string text)
{
    m_text = text;

    m_textWidth = align & Alignment::Left ? 0 : textWidth();
    refresh();
}

void Label::setAlignment(Alignment align)
{
    this->align = align;
    refresh();
}

void  Label::setColor(u_color color)
{
    m_color = color;
}

void Label::paint(MonitorDevice *const pMonitorDevice)
{
    if (m_text.length() == 0)
        return;

    pMonitorDevice->fillRect(screenRect, background());

    if (!visible)
        drawText(pMonitorDevice, {COLOR_24B_WHITE}, (Alignment) (
                     align | Alignment::Shift));

    u_color xcolor = { visible ? color().i_color : COLOR_24B_GREYD};
    drawText(pMonitorDevice, xcolor, align);
}

void Label::drawText(MonitorDevice *const pMonitorDevice, const u_color pxColor,
                     const Alignment align)
{
    int16_t vAlign = 0;
    if (align & Alignment::Bottom)
        vAlign = screenRect.height - font().height;
    else if (align & Alignment::VCenter)
        vAlign = (screenRect.height - font().height) / 2 ;
    //    else if (align & Alignment::Top)
    //        vAlign = 0;

    int16_t hAlign = 0;
    if (align & Alignment::Right)
        hAlign = screenRect.width - m_textWidth;
    else if (align & Alignment::HCenter)
        hAlign = (screenRect.width - m_textWidth) / 2 ;
    //    else if (align & Alignment::Left)
    //        hAlign = 0;

    if (align & Alignment::Shift)
    {
        vAlign ++;
        hAlign ++;
    }

    int16_t vAlignPos = vAlign < 0 ? abs(vAlign) : 0;
    int16_t posX = screenRect.x + hAlign;

    for (size_t n = 0; n < m_text.length(); ++n)
    {
        const IFont::CHAR_INFO *pDescriptor = descriptor(m_text.at(n));
        int8_t yPos = vAlignPos - pDescriptor->fstRow;
        yPos = yPos < 0 ? 0 : yPos;

        const uint8_t *pBitmaps = &font().bitmaps()[pDescriptor->position] + yPos;
        int16_t posY = screenRect.y + vAlign + pDescriptor->fstRow;

        uint16_t yMax = vAlign <= 0 ?
                        std::min(screenRect.height + screenRect.y, pDescriptor->sizeRow + posY) :
                        (pDescriptor->sizeRow + posY);
        for (uint8_t y = posY + yPos; y <  yMax; ++y)
        {
            uint8_t pt = 0;
            int16_t x = posX;
            for (uint8_t width = 0; width < pDescriptor->width; ++width)
            {
                if (x >= screenRect.x + screenRect.width)
                    break;

                if (IFont::Mode::Bitmap ==  font().mode)
                {
                    const uint8_t nBit = 7 - (width % 8);
                    if (nBit == 7)
                        pt = *(pBitmaps++);
                    if ( x >= screenRect.x)
                    {
                        bool px = pt >> nBit & 0x01;
                        if (!px)
                            pMonitorDevice->setPoint(x, y, pxColor);
                    }
                }
                else  // IFont::Mode::Antialias
                {
                    uint8_t pt = *(pBitmaps++);
                    if (pt != 0xFFU && x >= screenRect.x)
                    {
                        u_color foreground(pxColor);
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
