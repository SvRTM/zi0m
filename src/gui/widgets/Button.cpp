/*
 * Button.cpp
 *
 *  Created on: 2 февр. 2016 г.
 *      Author: Artem.Smirnov
 */

#include "Button.h"

namespace zi0m
{

Button::Button(Point pos, Size size, Widget *parent) :
#ifdef RGB888
    Additional({0x00D6D2D0U})
#elif RGB565
    Additional({0xD69AU})
#endif
, Widget(pos, size, parent)
, TextCharacters(Alignment::Center)
{
    TextCharacters::m_pos = {int16_t(2 * borderWidth), int16_t(2 * borderWidth)};
    TextCharacters::m_size = {uint16_t(size.width - 4 * borderWidth), uint16_t(size.height - 4 * borderWidth)};
    TextCharacters::updateAbsPosition(absolutePos);
}

void Button::setSize(Size size)
{
    TextCharacters::setSize({uint16_t(size.width - 4 * borderWidth), uint16_t(size.height - 4 * borderWidth)});
    Widget::setSize(size);
}

void Button::updateAllPosition()
{
    Widget::updateAllPosition();
    TextCharacters::updateAbsPosition(absolutePos);
}

void Button::event(EventType type)
{
    this->type = type;

    if (!isEnabled())
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
        colorBR = {COLOR_WHITE};
        colorTL = {COLOR_BLACK};

        u_color colorTL2({COLOR_GREYD});

        // left
        pMonitorDevice->fillRect({int16_t(screen().x + borderWidth), int16_t(screen().y + borderWidth),
                                  borderWidth, uint16_t(screen().height - 3 * borderWidth)
                                 }, colorTL2);
        // top
        pMonitorDevice->fillRect({int16_t(screen().x + 2 * borderWidth), int16_t(screen().y + borderWidth),
                                  uint16_t(screen().width - 4 * borderWidth), borderWidth
                                 }, colorTL2);

        drawText(pMonitorDevice, color(), 1, 1);
    }
    else
    {
        colorBR = {COLOR_BLACK};
        colorTL = {COLOR_WHITE};

        u_color colorBR2({COLOR_GREYD});

        // bottom
        pMonitorDevice->fillRect({int16_t(screen().x + borderWidth), int16_t(screen().y + screen().height - 2 * borderWidth),
                                  uint16_t(screen().width - 3 * borderWidth), borderWidth
                                 }, colorBR2);
        // right
        pMonitorDevice->fillRect({int16_t(screen().x + screen().width - 2 * borderWidth), int16_t(screen().y + borderWidth),
                                  borderWidth, uint16_t(screen().height - 2 * borderWidth)
                                 }, colorBR2);

        drawText(pMonitorDevice);
    }

    // bottom
    pMonitorDevice->fillRect({screen().x, int16_t(screen().y + screen().height - borderWidth),
                              uint16_t(screen().width - borderWidth), borderWidth
                             }, colorBR);
    // right
    pMonitorDevice->fillRect({int16_t(screen().x + screen().width - borderWidth), screen().y,
                              borderWidth, screen().height
                             }, colorBR);

    // left
    pMonitorDevice->fillRect({screen().x, screen().y, borderWidth,
                              uint16_t(screen().height - borderWidth)
                             }, colorTL);
    // top
    pMonitorDevice->fillRect({screen().x, screen().y,
                              uint16_t(screen().width - borderWidth), borderWidth
                             }, colorTL);
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

}
