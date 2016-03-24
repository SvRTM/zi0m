/*
 * Button.cpp
 *
 *  Created on: 2 февр. 2016 г.
 *      Author: Artem.Smirnov
 */

#include "Button.h"

Button::Button(Widget *parent)
    : Widget(parent), borderWidth(1)
{
    label = new Label(this, Alignment::Center);
    addWidget(label);
}
Button::~Button()
{
}

void Button::setGeometry(Rect rect)
{
    Widget::setGeometry(rect);
    label->setGeometry(Rect(2 * borderWidth, 2 * borderWidth,
                            rect.width - 4 * borderWidth, rect.height - 4 * borderWidth));
}

void Button::setText(const std::u16string text)
{
    label->setText(text);
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

void Button::setVisible(bool visible)
{
    Widget::setVisible(visible);
    label->setVisible(visible);
}

void Button::paint(MonitorDevice *const pMonitorDevice)
{
    pMonitorDevice->fillRect(screenRect, {0x00D6D2D0U});

    u_color colorTL, colorBR;

    if (EventType::TouchButtonPress == eventType())
    {
        colorBR = {COLOR_24B_WHITE};
        colorTL = {COLOR_24B_BLACK};

        u_color colorTL2({COLOR_24B_GREYD});

        // left
        pMonitorDevice->fillRect(
            Rect(screenRect.x + borderWidth, screenRect.y + borderWidth, borderWidth,
                 screenRect.height - 3 * borderWidth), colorTL2);
        // top
        pMonitorDevice->fillRect(
            Rect(screenRect.x + 2 * borderWidth, screenRect.y + borderWidth,
                 screenRect.width - 4 * borderWidth, borderWidth), colorTL2);

        label->setAlignment((Alignment) (label->alignment() | Alignment::Shift));
    }
    else
    {
        colorBR = {COLOR_24B_BLACK};
        colorTL = {COLOR_24B_WHITE};

        u_color colorBR2({COLOR_24B_GREYD});

        // bottom
        pMonitorDevice->fillRect(
            Rect(screenRect.x + borderWidth,
                 screenRect.y + screenRect.height - 2 * borderWidth,
                 screenRect.width - 3 * borderWidth, borderWidth), colorBR2);
        // right
        pMonitorDevice->fillRect(
            Rect(screenRect.x + screenRect.width - 2 * borderWidth,
                 screenRect.y + borderWidth,
                 borderWidth, screenRect.height - 2 * borderWidth), colorBR2);

        label->setAlignment(Alignment::Center);
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
        Rect(screenRect.x, screenRect.y, borderWidth, screenRect.height - borderWidth),
        colorTL);
    // top
    pMonitorDevice->fillRect(
        Rect(screenRect.x, screenRect.y, screenRect.width - borderWidth, borderWidth),
        colorTL);
}
