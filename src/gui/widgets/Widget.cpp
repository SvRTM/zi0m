/*
 * Copyright © 2016 Artem Smirnov
 * All right reserved.
 * Author: Artem Smirnov <msvrtm@gmail.com>
 * License: http://www.gnu.org/licenses/gpl.txt
 */

#include "Widget.h"
#include "gui/text/TextCharacters.h"

namespace zi0m
{
const Rect Widget::zeroBorder = 0;

Widget::Widget(Point pos, Size size, Widget *const parent, const Rect &border)
    : m_pos(pos), m_size(size), m_parent(parent),
    absolutePos({int16_t(parent ? parent->absoluteClientPos.x + parent->Border().x + m_pos.x : m_pos.x + border.x),
                int16_t(parent ? parent->absoluteClientPos.y + parent->Border().y + m_pos.y : m_pos.y + border.y)
})
{
    widgets.reserve(0);

    typeId = TypeTag(typeId | TypeTag::WIDGET);

    absoluteClientPos = {int16_t(m_parent ? m_parent->absoluteClientPos.x + m_parent->Border().x + m_pos.x : m_pos.x + border.x),
                         int16_t(m_parent ? m_parent->absoluteClientPos.y + m_parent->Border().y + m_pos.y : m_pos.y + border.y)
                        };
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
        resetEvent();
    }

    for (Widget *const w : widgets)
    {
        if (w->isVisible())
            w->eventPaint(pMonitorDevice);
        else
            w->resetEvent();
    }
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
    absolutePos = {int16_t(m_parent ? m_parent->absolutePos.x  + m_parent->Border().x + m_pos.x : m_pos.x),
                   int16_t(m_parent ? m_parent->absolutePos.y  + m_parent->Border().y + m_pos.y : m_pos.y)
                  };

    absoluteClientPos = {int16_t(m_parent ? m_parent->absoluteClientPos.x + m_parent->Border().x + m_pos.x : m_pos.x + Border().x),
                         int16_t(m_parent ? m_parent->absoluteClientPos.y + m_parent->Border().y + m_pos.y : m_pos.y + Border().y)
                        };

    for (Widget *const w : widgets)
        w->updateAllPosition();

    refresh();
}

void Widget::refreshAll()
{
    refreshChilds();
}
void Widget::refreshChilds()
{
    refresh();
    for (Widget *const w : widgets)
        w->refreshChilds();
}

std::vector<Widget *> Widget::childs() const
{
    return widgets;
}

//FIXME: implement other option visible or not visible elements
void Widget::setVisible(bool visible)
{
    this->visible = visible;
    if (m_parent == nullptr)
        return;

    if (visible)
    {
        m_parent->refresh(false);
        refreshChilds();
    }
    else
        m_parent->refresh();
}

EventType Widget::eventType() const
{
    return type;
}

void Widget::addWidget(Widget *const w)
{
    widgets.push_back(w);
}

Widget *Widget::findWidget(const Point &pos) const
{
    for (Widget *const w : widgets)
    {
        Point &absPos = w->absolutePos;
        if ((absPos.x <= pos.x && absPos.x + w->m_size.width >= pos.x)
                && (absPos.y <= pos.y && absPos.y + w->m_size.height >= pos.y)
                && w->visible)
        {
            Widget *const chd = w->findWidget(pos);
            if (chd == nullptr)
                return w;
            return chd;
        }
    }
    return nullptr;
}

}
