/*
 * Widget.cpp
 *
 *  Created on: 25 янв. 2016 г.
 *      Author: Artem.Smirnov
 */

#include "Widget.h"
#include<iostream>
Widget::Widget()
{
    // this->pMonitorDevice = pMonitorDevice;
    visible = true;
    type = EventType::None;
    _refresh = true;
    pEventCtrl = new EventCtrl();
    parent = nullptr;

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

void Widget::paint(MonitorDevice *pMonitorDevice)
{
    for (Widget *w : widgets)
    {
        w->paint(pMonitorDevice);
    }
}

Rect *Widget::geometry()
{
    return &rect;
}
void Widget::setGeometry(Rect rect)
{
    this->rect = rect;
    screenRect = frameGeometry();
    std::cout << "geometry: " << rect.x << ":" << screenRect.x << "    "
            << rect.y << ":" << screenRect.y << std::endl << std::endl;
}

Rect Widget::frameGeometry()
{
    if (parent == nullptr)
        return rect;
    return parent->frameGeometry() + rect;
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
