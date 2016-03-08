/*
 * Button.cpp
 *
 *  Created on: 2 февр. 2016 г.
 *      Author: Artem.Smirnov
 */

#include "Button.h"

#include <iostream>

Button::Button(Widget *parent, Alignment align)
        : Widget(parent), borderWidth(1)
{
    this->align = align;
    label = new Label(this);
    add(label);
}
Button::~Button()
{
}

void Button::setGeometry(Rect rect)
{
    //label->setGeometry(
    //        Rect(2 * borderWidth, 2 * borderWidth, rect.width - 2 * borderWidth,
    //                rect.height - 2 * borderWidth));
    sPressed.rect = Rect(2 * borderWidth, 2 * borderWidth,
            rect.width - 4 * borderWidth, rect.height - 4 * borderWidth);
    Widget::setGeometry(rect);
}

void Button::setText(const std::u16string text)
{
    m_text = text;
    label->setText(m_text);
}

void Button::pressed()
{
    setEventType(EventType::TouchButtonPress);
    refresh();
}

void Button::released()
{
    setEventType(EventType::TouchButtonRelease);
    refresh();
}

void Button::paint(MonitorDevice * const pMonitorDevice)
{
    if (!isVisible())
        return;

    pMonitorDevice->fillRect(screenRect, u_color { 0x00D6D2D0U });

    u_color colorTL, colorBR;

    if (EventType::TouchButtonPress == eventType())
    {
        colorBR.i_color = COLOR_24B_WHITE;
        colorTL.i_color = COLOR_24B_BLACK;

        u_color colorTL2;
        colorTL2.i_color = COLOR_24B_GREYD;

        // left
        pMonitorDevice->fillRect(
                Rect(screenRect.x + borderWidth, screenRect.y + borderWidth,
                        borderWidth, screenRect.height - 3 * borderWidth),
                colorTL2);
        // top
        pMonitorDevice->fillRect(
                Rect(screenRect.x + 2 * borderWidth, screenRect.y + borderWidth,
                        screenRect.width - 4 * borderWidth, borderWidth),
                colorTL2);

        const Rect *r = label->geometry();
        sPressed.rect = Rect(r->x, r->y, r->width, r->height);
        label->setGeometry(
                Rect(r->x + 2 * borderWidth, r->y + 2 * borderWidth, r->width,
                        r->height));
    } else
    {
        colorBR.i_color = COLOR_24B_BLACK;
        colorTL.i_color = COLOR_24B_WHITE;

        u_color colorBR2;
        colorBR2.i_color = COLOR_24B_GREYD;

        // bottom
        pMonitorDevice->fillRect(
                Rect(screenRect.x + borderWidth,
                        screenRect.y + screenRect.height - 2 * borderWidth,
                        screenRect.width - 3 * borderWidth, borderWidth),
                colorBR2);
        // right
        pMonitorDevice->fillRect(
                Rect(screenRect.x + screenRect.width - 2 * borderWidth,
                        screenRect.y + borderWidth, borderWidth,
                        screenRect.height - 2 * borderWidth), colorBR2);

        label->setGeometry(sPressed.rect);
    }

    // bottom
    pMonitorDevice->fillRect(
            Rect(screenRect.x, screenRect.y + screenRect.height - borderWidth,
                    screenRect.width - borderWidth, borderWidth), colorBR);
    // right
    pMonitorDevice->fillRect(
            Rect(screenRect.x + screenRect.width - borderWidth, screenRect.y,
                    borderWidth, screenRect.height), colorBR);

    // left
    pMonitorDevice->fillRect(
            Rect(screenRect.x, screenRect.y, borderWidth,
                    screenRect.height - borderWidth), colorTL);
    // top
    pMonitorDevice->fillRect(
            Rect(screenRect.x, screenRect.y, screenRect.width - borderWidth,
                    borderWidth), colorTL);
}
