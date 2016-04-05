/*
 * Button.cpp
 *
 *  Created on: 2 февр. 2016 г.
 *      Author: Artem.Smirnov
 */

#include "Button.h"

Button::Button(Widget *parent) : Additional({0x00D6D2D0U}),
       Widget(parent), TextCharacters(Alignment::Center), borderWidth(1)
{
}

void Button::setGeometry(Rect rect)
{
    TextCharacters::setGeometry(Rect(2 * borderWidth, 2 * borderWidth,
                                     rect.width - 4 * borderWidth, rect.height - 4 * borderWidth));
    Widget::setGeometry(rect);
}

void Button::updateGeometry()
{
    Widget::updateGeometry();
    TextCharacters::updateTextAbsPosition(screen());
}

void Button::setText(const std::u16string text)
{
    TextCharacters::setText(text);
    refresh();
}

void  Button::setColor(u_color color)
{
    m_color = color;
    refresh();
}

void Button::event(EventType type)
{
    this->type = type;

    if (!visible)
        return;

    switch (type)
    {
        case EventType::TouchStart:
            if (cbPressed)
                cbPressed();
            goto L;
        case EventType::TouchEnd:
            if (cbReleased)
                cbReleased();
            goto L;

        case EventType::TouchLeave:
            if (cbMoved)
                cbMoved(0, 0);
        L:
            refresh();
            break;

        default:
            break;
    }
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

void Button::setCbMoved(const std::function<void (uint16_t, uint16_t)> &func)
{
    cbMoved = func;
}

void Button::setCbReleased(const std::function<void ()> &func)
{
    cbReleased = func;
}

void Button::setCbPressed(const std::function<void ()> &func)
{
    cbPressed = func;
}
