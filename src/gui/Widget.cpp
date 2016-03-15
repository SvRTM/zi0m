/*
 * Widget.cpp
 *
 *  Created on: 25 янв. 2016 г.
 *      Author: Artem.Smirnov
 */

#include "Widget.h"


Widget::Widget()
    : parent(nullptr)
{
    font = &Singleton<ONE_BIT_COLOR>::instance();
    pEventCtrl = new EventCtrl();

    rect = {};
    screenRect = {};

    visible = true;
    m_refresh = true;

    type = EventType::_None;
}
Widget::Widget(Widget *const parent)
    : Widget()
{
    this->parent = parent;
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
    for (Widget *w : widgets)
        w->eventPaint(pMonitorDevice);
}

const Rect *Widget::geometry() const
{
    return &rect;
}

void Widget::setGeometry(Rect rect)
{
    this->rect = rect;
    updateGeometry();
    refresh();
}

void Widget::updateGeometry()
{
    screenRect = frameGeometry();
    for (Widget *w : widgets)
        w->updateGeometry();
}

const Rect Widget::frameGeometry()
{
    if (parent == nullptr)
        return rect;
    Rect parentRect = parent->screenRect;
    return parentRect + rect;
}

bool Widget::isVisible() const
{
    return visible;
}
void Widget::setVisible(bool visible)
{
    this->visible = visible;
}

void Widget::setEventType(EventType type)
{
    this->type = type;
}

EventType Widget::eventType() const
{
    return type;
}

void Widget::addWidget(Widget *const w)
{
    widgets.push_back(w);
}
Widget *Widget::findChild(int16_t x, int16_t y) const
{
    for (Widget *w : widgets)
        if (w->screenRect.contains(x, y))
            return w;

    return nullptr;
}
