/*
 * Widget.cpp
 *
 *  Created on: 25 янв. 2016 г.
 *      Author: Artem.Smirnov
 */

#include "Widget.h"

#include "font/Terminus_11pt_Regular.h"

Widget::Widget(Widget *const _parent)
    : parent(_parent), pEventCtrl(new EventCtrl()),
    m_font(&Singleton<Terminus_11pt_Regular>::instance()), m_bg({0x00E8F6FAU}),
    type(EventType::_None), visible(true), m_refresh(true)
{
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

void Widget::setFont(const IFont &font)
{
    m_font = &font;
}

void Widget::setBackground(const u_color bg)
{
    m_bg = bg;
}

void Widget::setVisible(bool visible)
{
    this->visible = visible;
    refresh();
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
