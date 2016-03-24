/*
 * Label.cpp
 *
 *  Created on: 6 марта 2016 г.
 *      Author: Artem.Smirnov
 */

#include "Label.h"
#include <iostream>
using namespace std;
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

    u_color xcolor;
    if (IFont::Mode::Bitmap ==  font().mode)
    {
        if (!visible)
        {
            xcolor.i_color = COLOR_24B_WHITE;
            drawTextMonochrome(pMonitorDevice, xcolor, Alignment::Shift);
        }
        xcolor.i_color = visible ? color().i_color : COLOR_24B_GREYD;
        drawTextMonochrome(pMonitorDevice, xcolor, align);
    }
    else
        drawText(pMonitorDevice, align, color());
}

void Label::drawTextMonochrome(MonitorDevice *const pMonitorDevice,
                               const u_color pxColor,
                               const Alignment align)
{
    int16_t vAlign = 0;
    if (align & Alignment::Bottom)
        vAlign = screenRect.height - font().height;
    else if (align & Alignment::VCenter)
        vAlign = (screenRect.height - font().height) / 2 ;
    else if (align & Alignment::Shift)
        vAlign = (screenRect.height - font().height) / 2 + 1 ;
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

    for (size_t n = 0; n < m_text.length(); ++n)
    {
        const IFont::CHAR_INFO *pDescriptor = descriptor(m_text.at(n));
        int8_t d = vAlignPos - pDescriptor->fstRow;
        const uint8_t *pBitmaps = &font().bitmaps()[pDescriptor->position] +
                                  (d < 0 ? 0 : d);
        int16_t y = screenRect.y + vAlign + pDescriptor->fstRow;

        uint16_t e = vAlign <= 0 ?
                     std::min(screenRect.height + screenRect.y, pDescriptor->sizeRow + y) :
                     (pDescriptor->sizeRow + y);

        for (uint8_t yRow = y + (d < 0 ? 0 : d); yRow <  e; ++yRow)
        {
            int16_t x = scrX;
            uint8_t pt = 0;
            for (uint8_t width = 0; width < pDescriptor->width; ++width)
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
                        pMonitorDevice->setPoint(x, yRow, pxColor);
                }
                x++;
            }
        }
        scrX += pDescriptor->width;
    }
}

void Label::drawText(MonitorDevice *const pMonitorDevice, const Alignment align,
                     const u_color pxColor)
{
    int16_t vAlign = 0;
    if (align & Alignment::Bottom)
        vAlign = screenRect.height - font().height;
    else if (align & Alignment::VCenter)
        vAlign = (screenRect.height - font().height) / 2 ;
    else if (align & Alignment::Shift)
        vAlign = (screenRect.height - font().height) / 2 + 1 ;
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
    cout << endl << endl << endl;
    for (size_t n = 0; n < m_text.length(); ++n)
    {
        const IFont::CHAR_INFO *pDescriptor = descriptor(m_text.at(n));
        int8_t d = vAlignPos - pDescriptor->fstRow;
        const uint8_t *pBitmaps = &font().bitmaps()[pDescriptor->position] +
                                  (d < 0 ? 0 : d);
        int16_t y = screenRect.y + vAlign + pDescriptor->fstRow;

        uint16_t e = vAlign <= 0 ?
                     std::min(screenRect.height + screenRect.y, pDescriptor->sizeRow + y) :
                     (pDescriptor->sizeRow + y);
cout<<endl;
        for (uint8_t yRow = y + (d < 0 ? 0 : d); yRow <  e; ++yRow)
        {
            int16_t x = scrX;
            uint8_t pt = 0;
            for (uint8_t width = 0; width < pDescriptor->width; ++width)
            {
                if (x >= screenRect.x + screenRect.width)
                    break;
                pt = *(pBitmaps++);
                if (pt != 0xFFU && x >= screenRect.x)
                {
                    float bh, bs, bl;
                    RGBToHSL(background(), bh, bs, bl);

                    float h, s, l;
                    RGBToHSL(pxColor, h, s, l);
                    float  q = pt / (255.0f);
                    cout<<"\t[l:"<<l<< ", pt:"<<int(pt);
                    float _l = l;
                    l = (1.0f - l) * q + l;
                    cout<<"  new l:"<<l<<"]";
                    u_color foreground;
                    foreground = HSLToRGB(h, s, l);
                    //foreground.uc_color.A =255-(pt);// (1.0-l)*255;
                    foreground = pxColor;
                    foreground.uc_color.A = 255-pt;//==0? 255:(1.0- l)*255;
                    cout<<"\t[l:"<<l<<", A:"<<(int)foreground.uc_color.A<<"]  "<<endl;
                    foreground = pMonitorDevice->alphaBlending(foreground, background());

                        pMonitorDevice->setPoint(x, yRow, foreground);
                }
                x++;
            }
        }
        scrX += pDescriptor->width;
    }
}
