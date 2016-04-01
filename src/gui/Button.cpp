/*
 * Button.cpp
 *
 *  Created on: 2 февр. 2016 г.
 *      Author: Artem.Smirnov
 */

#include "Button.h"

Button::Button(Widget *parent)
    : Widget(parent), TextCharacters(Alignment::Center), borderWidth(1)
{
    setBackground({0x00D6D2D0U});
}
Button::~Button()
{
}

void Button::setGeometry(Rect rect)
{
    Widget::setGeometry(rect);
    setAbsolutePosition(Rect(
                            screen().x +  2 * borderWidth, screen().y + 2 * borderWidth,
                            screen().width - 4 * borderWidth, screen().height - 4 * borderWidth));
}

void Button::setText(const std::u16string text)
{
    TextCharacters::setText(text);
    refresh();
}

void  Button::setColor(u_color color)
{
    TextCharacters::setColor(color);
    refresh();
}

void Button::pressed()
{
    setEventType(EventType::TouchStart);
    refresh();
}

void Button::released()
{
    setEventType(EventType::TouchEnd);
    refresh();
}

void Button::paint(MonitorDevice *const pMonitorDevice)
{
    pMonitorDevice->fillRect(screen(), background());

    u_color colorTL, colorBR;

    if (EventType::TouchStart == eventType())
    {
        colorBR = {COLOR_24B_WHITE};
        colorTL = {COLOR_24B_BLACK};

        u_color colorTL2({COLOR_24B_GREYD});

        // left
        pMonitorDevice->fillRect(Rect(
                                     screen().x + borderWidth, screen().y + borderWidth, borderWidth,
                                     screen().height - 3 * borderWidth), colorTL2);
        // top
        pMonitorDevice->fillRect(Rect(
                                     screen().x + 2 * borderWidth, screen().y + borderWidth,
                                     screen().width - 4 * borderWidth, borderWidth), colorTL2);

        drawText(pMonitorDevice, color(), 1, 1);
    }
    else
    {
        colorBR = {COLOR_24B_BLACK};
        colorTL = {COLOR_24B_WHITE};

        u_color colorBR2({COLOR_24B_GREYD});

        // bottom
        pMonitorDevice->fillRect(
            Rect(screen().x + borderWidth, screen().y + screen().height - 2 * borderWidth,
                 screen().width - 3 * borderWidth, borderWidth), colorBR2);
        // right
        pMonitorDevice->fillRect(
            Rect(screen().x + screen().width - 2 * borderWidth, screen().y + borderWidth,
                 borderWidth, screen().height - 2 * borderWidth), colorBR2);

        drawText(pMonitorDevice);
    }

    // bottom
    pMonitorDevice->fillRect(
        Rect(screen().x, screen().y + screen().height - borderWidth,
             screen().width - borderWidth, borderWidth), colorBR);
    // right
    pMonitorDevice->fillRect(
        Rect(screen().x + screen().width - borderWidth, screen().y,
             borderWidth, screen().height), colorBR);

    // left
    pMonitorDevice->fillRect(
        Rect(screen().x, screen().y, borderWidth, screen().height - borderWidth),
        colorTL);
    // top
    pMonitorDevice->fillRect(
        Rect(screen().x, screen().y, screen().width - borderWidth, borderWidth),
        colorTL);
}
