/*
 * Widget.cpp
 *
 *  Created on: 25 янв. 2016 г.
 *      Author: Artem.Smirnov
 */

#include "Widget.h"
#include<iostream>

const ONE_BIT_COLOR Terminus_11;

Widget::Widget()
{
    visible = true;
    type = EventType::None;
    _refresh = true;
    pEventCtrl = new EventCtrl();
    parent = nullptr;

    font = &Terminus_11;
}
Widget::Widget(Widget* parent)
        : Widget()
{
    this->parent = parent;
}
Widget::~Widget()
{
    for (Widget *pWidget : widgets)
        delete pWidget;
}

void Widget::eventPaint(MonitorDevice *pMonitorDevice)
{
    if (_refresh)
    {
        paint(pMonitorDevice);
        _refresh = false;
    }
    for (Widget *w : widgets)
        w->eventPaint(pMonitorDevice);
}

Rect *Widget::geometry()
{
    return &rect;
}

void Widget::setGeometry(Rect rect)
{
    this->rect = rect;
    screenRect = frameGeometry();
    updateGeometry();

}

void Widget::updateGeometry()
{
    screenRect = frameGeometry();
    for (Widget *w : widgets)
        w->updateGeometry();
}

Rect Widget::frameGeometry()
{
    if (parent == nullptr)
        return rect;
    //return parent->frameGeometry() + rect;
    return parent->screenRect + rect;
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

void Widget::add(Widget *w)
{
    widgets.push_back(w);
}
Widget *Widget::find(int x, int y)
{
    for (Widget *w : widgets)
        if (w->screenRect.contains(x, y))
            return w;

    return nullptr;
}
