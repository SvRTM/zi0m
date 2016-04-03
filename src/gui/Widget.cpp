/*
 * Widget.cpp
 *
 *  Created on: 25 янв. 2016 г.
 *      Author: Artem.Smirnov
 */

#include "Widget.h"
#include "TextCharacters.h"

Widget::Widget(Widget *const parent)
    :  type(EventType::_None), parent(parent), m_refresh(true)
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
    for (Widget *const w : widgets)
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
    for (Widget *const w : widgets)
    {
        TextCharacters *const txtCh  = dynamic_cast<TextCharacters *const>(w);
        if (txtCh)
            txtCh->updateGeometry();
        else
            w->updateGeometry();
    }
}

const Rect Widget::frameGeometry()
{
    if (parent == nullptr)
        return rect;
    Rect parentRect = parent->screenRect;
    return parentRect + rect;
}

void Widget::setEnabled(bool enable)
{
    enabled = enable;
    if (parent)
        parent->refresh();
}

void Widget::setVisible(bool visible)
{
    Additional::setVisible(visible);
    refresh();
}

EventType Widget::eventType() const
{
    return type;
}

void Widget::addWidget(Widget *const w)
{
    widgets.push_back(w);
}

Widget *const Widget::exFindChild(int16_t x, int16_t y) const
{
    for (Widget *const w : widgets)
        if (w->screenRect.contains(x, y) && w->enabled)
        {
            Widget *const _w = w->exFindChild(x, y);
            if (_w == nullptr)
                return w;
            return _w;
        }

    return nullptr;
}
