/*
 * Label.cpp
 *
 *  Created on: 6 марта 2016 г.
 *      Author: Artem.Smirnov
 */

#include "Label.h"
#include <iostream>

Label::Label(Widget *parent)
        : Widget(parent)
{
    m_pText = nullptr;
}
Label::~Label()
{
}

void Label::setText(const std::u16string &str)
{
    m_pText = &str;
    refresh();
}

void Label::paint(MonitorDevice * const pMonitorDevice)
{
    if (m_pText == nullptr)
        return;

    int16_t scrX = screenRect.x;
    u_color blkColor;
    blkColor.i_color = COLOR_24B_BLACK;

    int16_t yy = screenRect.y + ((screenRect.height - font->height) / 2);

    for (size_t i = 0; i < m_pText->length(); i++)
    {
        const ONE_BIT_COLOR::CHAR_INFO *pDescriptor = descriptor(
                m_pText->at(i));
        if (pDescriptor == nullptr)
            // TODO: unknown symbol, draw a rectangle '⛿'
            continue;

        const uint8_t *pBitmaps = &font->bitmaps[pDescriptor->position];

        int16_t y = /*screenRect.y*/yy + pDescriptor->fstRow;
        for (uint8_t nRow = 0;
                nRow <= pDescriptor->lstRow - pDescriptor->fstRow; nRow++)
        {
            int16_t x = scrX;
            uint8_t pt = 0;
            for (uint8_t width = 0; width < pDescriptor->width; width++)
            {
                if (x >= screenRect.x + screenRect.width
                        || y + nRow >= screenRect.y + screenRect.height)
                    break;

                const uint8_t nBit = 7 - (width % 8);
                if (nBit == 7)
                    pt = *(pBitmaps++);

                bool px = pt >> nBit & 0x01;
                if (!px)
                    pMonitorDevice->setPoint(x, y + nRow, blkColor);
                x++;
            }
        }
        scrX += pDescriptor->width;
    }
}

