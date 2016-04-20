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
    :  type(EventType::None)
    , absolutePos(parent ? parent->absolutePos + pos : pos)
    , m_pos(pos), m_size(size), m_parent(parent)
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
    {
        if (w->isVisible())
            w->eventPaint(pMonitorDevice);
        w->resetEvent();
    }
    resetEvent();
}

void Widget::setPosition(Point pos)
{
    m_pos = pos;
    updateAllPosition();
}

void Widget::setSize(const Size size)
{
    m_size = size;
    updateAllPosition();
}

void Widget::setEnabledChilds(bool enabled)
{
    for (Widget *const w : widgets)
        w->setEnabled(enabled);
}

void Widget::setEnabled(bool enabled)
{
    setEnabledChilds(enabled);

    this->enabled = enabled;
    refresh();
}

void Widget::updateAllPosition()
{
    absolutePos = m_parent ? m_parent->absolutePos + m_pos : m_pos;

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

void Widget::refreshChilds()
{
    refresh();
    for (Widget *const w : widgets)
        w->refreshChilds();
}

//FIXME: implement other option visible or not visible elements
void Widget::setVisible(bool visible)
{
    this->visible = visible;
    if (m_parent)
    {
        if (visible)
        {
            m_parent->refresh(false);
            refreshChilds();
        }
        else
            m_parent->refresh();
    }
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
