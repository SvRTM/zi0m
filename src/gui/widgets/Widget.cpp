/*
 * Widget.cpp
 *
 *  Created on: 25 янв. 2016 г.
 *      Author: Artem.Smirnov
 */

#include "Widget.h"
#include "gui/text/TextCharacters.h"

namespace zi0m
{

Widget::Widget(Point pos, Size size, Widget *const parent)
    :  type(EventType::_None),
       absolutePos(parent ? parent->absolutePos + pos : pos),
       m_pos(pos), m_size(size), parent(parent)
{
    updateAllPosition();
}
Widget::~Widget()
{
    for (Widget *pWidget : widgets)
        delete pWidget;
}

void Widget::eventPaint(MonitorDevice *const pMonitorDevice)
{
    if (m_refresh)
    {
        paint(pMonitorDevice);
        m_refresh = false;
    }
    for (Widget *const w : widgets)
        w->eventPaint(pMonitorDevice);
}

void Widget::setPosition(Point pos)
{
    m_pos = pos;
    updateAllPosition();
}

void Widget::setSize(Size size)
{
    m_size = size;
    updateAllPosition();
}

void Widget::updateAllPosition()
{
    absolutePos = parent ? parent->absolutePos + m_pos : m_pos;

    for (Widget *const w : widgets)
    {
        TextCharacters *const txtCh  = dynamic_cast<TextCharacters *const>(w);
        if (txtCh)
            txtCh->updateAllPosition();
        else
            w->updateAllPosition();
    }
    refresh();
}

void Widget::setVisible(bool visible)
{
    this->visible = visible;
    if (parent)
        parent->refresh();
}

EventType Widget::eventType() const
{
    return type;
}

void Widget::addWidget(Widget *const w)
{
    widgets.push_back(w);
}

Widget *const Widget::findWidget(int16_t x, int16_t y) const
{
    for (Widget *const w : widgets)
    {
        Point &absPos = w->absolutePos;
        if ((absPos.x <= x && absPos.x + w->m_size.width >= x)
                && (absPos.y <= y && absPos.y + w->m_size.height >= y)
                && w->visible)
        {
            Widget *const chd = w->findWidget(x, y);
            if (chd == nullptr)
                return w;
            return chd;
        }
    }
    return nullptr;
}

}
