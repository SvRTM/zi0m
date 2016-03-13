/*
 * Label.cpp
 *
 *  Created on: 6 марта 2016 г.
 *      Author: Artem.Smirnov
 */

#include "Label.h"
#include <iostream>
using namespace std;

Label::Label(Widget *parent, uint8_t align)
        : Widget(parent), m_textWidth(0)
{
    this->align = align;
}
Label::~Label()
{
}

void Label::setText(const std::u16string str)
{
    m_pText = str;

    m_textWidth = align & Alignment::Left ? 0 : textWidth();
    refresh();
}

void Label::paint(MonitorDevice * const pMonitorDevice)
{
    if (m_pText.length() == 0)
        return;
    cout << endl << endl;

    u_color color;
    color.i_color = COLOR_24B_GREEN;
    pMonitorDevice->fillRect(screenRect, color);

    u_color blkColor;
    blkColor.i_color = COLOR_24B_BLACK;

    int16_t vAlign;
    if (align & Alignment::Bottom)
        vAlign = screenRect.height - font->height;
    else if (align & Alignment::HCenter)
        vAlign = (screenRect.height - font->height) / 2;
    else
        //Alignment::Top
        vAlign = 0;
    int16_t vAlignPos = vAlign < 0 ? abs(vAlign) : 0;

    int16_t hAlign;
    hAlign = (screenRect.width - m_textWidth) / 2;
    //int16_t hAlignPos = hAlign < 0 ? abs(hAlign) : 0;

    int16_t scrX = screenRect.x + hAlign;

    for (size_t i = 0; i < m_pText.length(); i++)
    {
        const ONE_BIT_COLOR::CHAR_INFO *pDescriptor = descriptor(m_pText.at(i));
        const uint8_t *pBitmaps = &font->bitmaps[pDescriptor->position]
                + (vAlignPos == 0 ? 0 : vAlignPos - pDescriptor->fstRow);

        int16_t y = screenRect.y + pDescriptor->fstRow + vAlign;
        for (uint8_t yRow = y
                + (vAlignPos == 0 ? 0 : vAlignPos - pDescriptor->fstRow);
                yRow < pDescriptor->sizeRow + y; yRow++)
        {
            int16_t x = scrX;

            uint8_t pt = 0;
            for (uint8_t width = 0; width < pDescriptor->width; width++)
            {
                //  if (x >= screenRect.x + screenRect.width
                //          || yRow >= screenRect.y + screenRect.height)
                //      break;

                const uint8_t nBit = 7 - (width % 8);
                if (nBit == 7)
                    pt = *(pBitmaps++);
                //if (x >= screenRect.x && yRow >= screenRect.y)
                {
                    bool px = pt >> nBit & 0x01;
                    if (!px)
                        pMonitorDevice->setPoint(x, yRow, blkColor);
                }
                x++;
            }
        }
        scrX += pDescriptor->width;
    }
}

