/*
 * Button.cpp
 *
 *  Created on: 2 февр. 2016 г.
 *      Author: Artem.Smirnov
 */

#include "Button.h"

#include <iostream>

Button::Button()
        : Widget()
{
    borderWidth = 1;
    label = new Label(this);
    label->setGeometry(Rect(1, 1, 10, 20));
    add(label);
}
Button::Button(Widget *parent)
        : Widget(parent)
{
    borderWidth = 1;
    label = new Label(this);
    label->setGeometry(Rect(1, 1, 55, 20));
    add(label);
}

Button::~Button()
{
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

void Button::paint(MonitorDevice *pMonitorDevice)
{
    //Rect screenRect = frameGeometry();
    pMonitorDevice->fillRect(screenRect, u_color { 0x00D6D2D0U });

    u_color colorTL, colorBR;

    if (!isVisible())
        return;

    if (EventType::TouchButtonPress == eventType())
    {
        colorBR.i_color = COLOR_24B_WHITE;
        colorTL.i_color = COLOR_24B_GREYD;
    } else
    {
        colorBR.i_color = COLOR_24B_GREYD;
        colorTL.i_color = COLOR_24B_WHITE;
    }

// Bot-Right Dark Border
    // LCD_SetTextColor(colorBR);
    //bot
    //std::cout << "~~x:" << screenRect.x << " y:" << screenRect.y << "  w:"
    //        << screenRect.width << " h:" << screenRect.height << std::endl;

    Rect t(screenRect.x + 1, screenRect.y + screenRect.height - borderWidth,
            screenRect.width - 1, borderWidth);
    pMonitorDevice->fillRect(t, colorBR);
    // right
    pMonitorDevice->fillRect(
            Rect(screenRect.x + screenRect.width - borderWidth,
                    screenRect.y + 1, borderWidth, screenRect.height - 1),
            colorBR);

    // Top-Left Light Border
    //LCD_SetTextColor(colorTL);
    // top
    pMonitorDevice->fillRect(
            Rect(screenRect.x, screenRect.y, borderWidth,
                    screenRect.height - 1), colorTL);
    // left
    pMonitorDevice->fillRect(
            Rect(screenRect.x, screenRect.y, screenRect.width - 1, borderWidth),
            colorTL);
}
