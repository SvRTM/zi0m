/*
 * Label.cpp
 *
 *  Created on: 6 марта 2016 г.
 *      Author: Artem.Smirnov
 */

#include "Label.h"

Label::Label(Widget *parent, uint8_t align)
    : Widget(parent), m_textWidth(0)
{
    this->align = align;
}
Label::~Label()
{
}

void Label::setText(const std::u16string text)
{
    m_text = text;

    m_textWidth = align & Alignment::Left ? 0 : textWidth();
    refresh();
}

void Label::setAlignment(uint8_t align)
{
    this->align = align;
    refresh();
}

void Label::paint(MonitorDevice *const pMonitorDevice)
{
    if (m_text.length() == 0)
        return;

    u_color color;
    color.i_color = COLOR_24B_GREEN;
    pMonitorDevice->fillRect(screenRect, color);

    u_color black;
    black.i_color = COLOR_24B_BLACK;

    int16_t vAlign = 0;
    if (align & Alignment::Bottom)
        vAlign = screenRect.height - font->height ;
    else if (align & Alignment::VCenter)
        vAlign = (screenRect.height - font->height) / 2 ;
    else if (align & Alignment::Shift)
        vAlign = (screenRect.height - font->height) / 2 + 1 ;
    //    else if (align & Alignment::Top)
    //        vAlign = 0;
    int16_t vAlignPos = vAlign < 0 ? abs(vAlign) : 0;


    int16_t hAlign = 0;
    if (align & Alignment::Right)
        hAlign = screenRect.width - m_textWidth;
    else if (align & Alignment::HCenter)
        hAlign = (screenRect.width - m_textWidth) / 2 ;
    else if (align & Alignment::Shift)
        hAlign = (screenRect.width - m_textWidth) / 2 + 1 ;
    //    else if (align & Alignment::Left)
    //        hAlign = 0;

    int16_t scrX = screenRect.x + hAlign;

    for (size_t n = 0; n < m_text.length(); n++)
    {
        const ONE_BIT_COLOR::CHAR_INFO *pDescriptor = descriptor(m_text.at(n));
        int8_t d = vAlignPos - pDescriptor->fstRow;
        const uint8_t *pBitmaps = &font->bitmaps[pDescriptor->position]
                                  + (d < 0 /*|| vAlignPos ==0*/ ? 0 : d);
        int16_t y = screenRect.y + vAlign + pDescriptor->fstRow;

        uint16_t e = vAlign <= 0 ?
                     std::min(screenRect.height + screenRect.y, pDescriptor->sizeRow + y) :
                     (pDescriptor->sizeRow + y);

        for (uint8_t yRow = y + (d < 0 /*|| vAlignPos ==0*/ ? 0 : d); yRow <  e; yRow++)
        {
            int16_t x = scrX;
            uint8_t pt = 0;
            for (uint8_t width = 0; width < pDescriptor->width; width++)
            {
                if (x >= screenRect.x + screenRect.width)
                    break;

                const uint8_t nBit = 7 - (width % 8);
                if (nBit == 7)
                    pt = *(pBitmaps++);
                if ( x >= screenRect.x)
                {
                    bool px = pt >> nBit & 0x01;
                    if (!px)
                        pMonitorDevice->setPoint(x, yRow, black);
                }
                x++;
            }
        }
        scrX += pDescriptor->width;
    }
}
