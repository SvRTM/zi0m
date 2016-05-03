#include "GroupBox.h"
#include "p_checkbox.h"

namespace zi0m
{

GroupBox::GroupBox(Point pos, Size size, Widget *const parent)
    : AbstractTextWidget(pos, size, Alignment(Alignment::VCenter | Alignment::Left), parent,
                         border)
    , x2Left(size.width), border({2, font().height, 2, font().height})
{
    typeId = TypeTag(typeId | TypeTag::GROUPBOX);
}

void GroupBox::p_setSize()
{
    calcPosition();
}
void GroupBox::p_setFont()
{
    border.y = font().height;
    updateAllPosition();
}
void GroupBox::p_setText()
{
    calcPosition();
}
void GroupBox::p_updateAllPosition()
{
    calcPosition();
}

void GroupBox::event(const EventType type, const Point &pos)
{
    if (!isEnabled())
        return;

    this->type = type;

    if (!checkable)
        return;

    Rect rect = {int16_t(screenClient().x + (x2Left < 0 ? 0 : x2Left)), screenClient().y,
                 uint16_t(x2Left < 0 ? x1Right : x1Right - x2Left), font().height
                };
    if (rect.contains(pos))
    {
        if (isEnableTouchLeave)
        {
            typeCheckBox = EventType::TouchEnter;
            isEnableTouchLeave = false;
        }
        else
        {
            typeCheckBox = type;
            if (EventType::TouchEnd == type)
            {
                checked = !checked;
                setEnabledChilds(checked);
            }
        }
    }
    else if (!isEnableTouchLeave)
    {
        typeCheckBox = EventType::TouchLeave;
        isEnableTouchLeave = true;
    }
    else
        typeCheckBox =  EventType::TouchMove;

    refresh();
}

void GroupBox::setCheckable(bool checkable)
{
    this->checkable = checkable;
    prepareAlignHCenter(align);
    calcPosition();
}

void GroupBox::setChecked(bool checked)
{
    this->checked = checked;
}

void GroupBox::prepareAlignHCenter(Alignment align)
{
    //    if (alignCenter)
    //        if (checkable)
    //            TextCharacters::setAlignment(Alignment((align ^ Alignment::HCenter) | Alignment::Left) );
    //        else if (align & Alignment::Left)
    //            TextCharacters::setAlignment(Alignment((align ^ Alignment::Left) | Alignment::HCenter) );
    //        else
    //            TextCharacters::setAlignment(align);
    //    else
    //        TextCharacters::setAlignment(align);

    TextCharacters::setAlignment(alignCenter
                                 ? (checkable
                                    ? Alignment((align ^ Alignment::HCenter) | Alignment::Left)
                                    : (align & Alignment::Left
                                       ? Alignment((align ^ Alignment::Left) | Alignment::HCenter)
                                       : align))
                                 : align);
}
void GroupBox::setAlignment(Alignment align)
{
    alignCenter = align & Alignment::HCenter;
    prepareAlignHCenter(align);
}

/*
[y1Left]             [x2Left] ------------------------------------------------------------------[x1Right] --- [y1Right]  <-- ..................................,
   ^---( i n d e n t )-^{ marg. CheckBox marg.} (textPadding) {T E X T} (textPadding)^--------------^        <-- indentFrameTop -`
    |          ^             ------------------------------------------------------------------------------                  |
    |   Alignment::(Left/Right)                                                                                                   |
    |                                                                                                                                       |
    --------------------|-------------------------------------------------------------------------------|--------------
*/
void GroupBox::calcPosition()
{
    if (text().length() == 0 && !checkable)
    {
        indentFrameTop = 0;
        return;
    }
    indentFrameTop = font().height / 2 - 1;

    TextCharacters::m_size.width = pxTextWidth();
    TextCharacters::m_size.height = font().height > size().height
                                    ? size().height
                                    : (checkable && font().height < p_checkbox::boxWidth
                                       ? p_checkbox::boxWidth
                                       : font().height);

    if (align & Alignment::Right)
    {
        if (checkable)
            x2Left = size().width - (p_checkbox::marginLeftRight + p_checkbox::boxWidth +
                                     p_checkbox::marginLeftRight) -
                     textPadding - pxTextWidth() - indent;
        else
            x2Left = size().width - textPadding - pxTextWidth() - indent;
        if (x2Left <= 0)
        {
            y1Left = font().height / 2;
            if (checkable)
                if (size().width - indent < pxTextWidth())
                    TextCharacters::m_size.width = size().width - indent;
                else
                    TextCharacters::m_size.width = size().width - x2Left
                                                   - (p_checkbox::marginLeftRight + p_checkbox::boxWidth + p_checkbox::marginLeftRight)
                                                   - textPadding - indent;
            else
                TextCharacters::m_size.width = size().width - textPadding - indent;
        }
        else
            y1Left = 0;
        x1Right = size().width - indent;

        if (font().height < size().height)
        {
            isWholeBottomLine = true;
            isVisibleLeftLine = true;
        }
        else
        {
            isWholeBottomLine = false;
            isVisibleLeftLine = false;
        }
    }
    else if (alignCenter)
    {
        if (checkable)
            x2Left = (size().width
                      - (p_checkbox::marginLeftRight + p_checkbox::boxWidth + p_checkbox::marginLeftRight)
                      - textPadding - pxTextWidth() - textPadding) / 2 ;
        else
            x2Left = (size().width  - textPadding - pxTextWidth() - textPadding) / 2;
        if (x2Left <= 0)
        {
            x1Right = size().width;
            y1Right = y1Left = font().height / 2;
            if (checkable)
            {
                TextCharacters::m_size.width = size().width
                                               - (p_checkbox::marginLeftRight + x2Left + p_checkbox::boxWidth +
                                                  p_checkbox::marginLeftRight)
                                               - textPadding - textPadding;
                if (TextCharacters::m_size.width > size().width)
                    TextCharacters::m_size.width = size().width;
            }
            else
                TextCharacters::m_size.width = size().width;
        }
        else
        {
            y1Right = y1Left = x2Left < 0 ? font().height / 2 : 0;
            x1Right = size().width - x2Left;
        }

        if (font().height < size().height)
        {
            isWholeBottomLine = true;
            isVisibleRightLine = true;
            isVisibleLeftLine = true;
        }
        else
        {
            isWholeBottomLine = false;
            isVisibleRightLine = false;
            isVisibleLeftLine = false;
        }
    }
    else // if (align & Alignment::Left)
    {
        x2Left = indent;
        if (checkable)
            x1Right = indent
                      + (p_checkbox::marginLeftRight + p_checkbox::boxWidth + p_checkbox::marginLeftRight)
                      + textPadding + pxTextWidth() + textPadding;
        else
            x1Right = indent + textPadding + pxTextWidth() + textPadding;
        if (x1Right >= size().width - 1)
        {
            x1Right = size().width;
            y1Right = font().height / 2;
            if (checkable)
                TextCharacters::m_size.width = size().width - indent
                                               - (p_checkbox::marginLeftRight + p_checkbox::boxWidth + p_checkbox::marginLeftRight)
                                               - textPadding - textPadding;
            else
                TextCharacters::m_size.width = size().width - indent - textPadding - textPadding;
        }
        else
            y1Right = 0;

        if (font().height < size().height)
        {
            isWholeBottomLine = true;
            isVisibleRightLine = true;
        }
        else
        {
            isWholeBottomLine = false;
            isVisibleRightLine = false;
        }
    }

    if (checkable)
    {
        TextCharacters::m_pos.x = x2Left
                                  + p_checkbox::marginLeftRight + p_checkbox::boxWidth + p_checkbox::marginLeftRight
                                  + textPadding;
        if (TextCharacters::m_pos.x < 0)
            TextCharacters::m_pos.x = 0;
    }
    else
        TextCharacters::m_pos.x = x2Left <= 0 ? 0 : x2Left + textPadding;

    TextCharacters::updateAbsPosition(absoluteClientPos);
}

void GroupBox::paint(MonitorDevice *const pMonitorDevice)
{
    if (typeCheckBox == EventType::TouchMove)
    {
        typeCheckBox = EventType::None;
        return;
    }

    if (typeCheckBox == EventType::TouchEnd || typeCheckBox == EventType::None)
    {
        pMonitorDevice->fillRect(screenClient(), background());

        Point chPos = {0, indentFrameTop};
        chPos.x += screenClient().x;
        chPos.y += screenClient().y;

        if (x2Left > 1)
        {
            //top-left
            pMonitorDevice->drawHLine(chPos.x + 1, chPos.y, x2Left - 1, {COLOR_GRAY});
            if (x2Left > 2)
                pMonitorDevice->drawHLine(chPos.x + 2, chPos.y + 1, x2Left - 2, {COLOR_WHITE});
        }
        if (y1Right == 0 )
        {
            //top-right
            pMonitorDevice->drawHLine(chPos.x + x1Right, chPos.y,
                                      size().width - x1Right - 1, {COLOR_GRAY});
            if (size().width - x1Right - 1 - 1 > 0)
                pMonitorDevice->drawHLine(chPos.x + x1Right, chPos.y + 1,
                                          size().width - x1Right - 1 - 1, {COLOR_WHITE});
        }

        if (isVisibleLeftLine)
        {
            // left
            pMonitorDevice->drawVLine(chPos.x, chPos.y + y1Left,
                                      size().height - y1Left - indentFrameTop - 1 - 1, {COLOR_GRAY});
            pMonitorDevice->drawVLine(chPos.x + 1, chPos.y + 1 + y1Left,
                                      1 + size().height - y1Left - indentFrameTop - 1 - 1 - 1 - 1, {COLOR_WHITE});
        }

        if (isVisibleRightLine)
        {
            // right
            pMonitorDevice->drawVLine(chPos.x + size().width - 1, chPos.y + y1Right,
                                      size().height - y1Right - indentFrameTop - 1 , {COLOR_WHITE});
            pMonitorDevice->drawVLine(chPos.x + size().width - 1 - 1, chPos.y + y1Right + 1,
                                      size().height - y1Right - indentFrameTop - 1 - 1 - 1, {COLOR_GRAY});
        }

        if (isVisibleLeftLine && isVisibleRightLine)
        {
            // bottom
            uint16_t x2 = isWholeBottomLine ? size().width : x2Left;
            pMonitorDevice->drawHLine(chPos.x, chPos.y + size().height - indentFrameTop - 1 - 1,
                                      x2 - 1, {COLOR_GRAY});
            pMonitorDevice->drawHLine(chPos.x, chPos.y + size().height - indentFrameTop - 1,
                                      x2, {COLOR_WHITE});

            if ( !isWholeBottomLine)
            {
                pMonitorDevice->drawHLine(chPos.x + x1Right,
                                          chPos.y + size().height - indentFrameTop - 1 - 1,
                                          size().width - x1Right - 1, {COLOR_GRAY});
                pMonitorDevice->drawHLine(chPos.x + x1Right,
                                          chPos.y + size().height - indentFrameTop - 1,
                                          size().width - x1Right, {COLOR_WHITE});
            }
        }

        drawText(pMonitorDevice,
                 checkable && alignCenter && x2Left < 0
                 ? (TextCharacters::m_pos.x == 0
                    ? x2Left + p_checkbox::marginLeftRight + p_checkbox::boxWidth +
                    p_checkbox::marginLeftRight + textPadding
                    : 0)
                 : 0);
    }

    if (checkable)
        paintCheckBox(pMonitorDevice);
}

void GroupBox::paintCheckBox(MonitorDevice *const pMonitorDevice)
{
    u_color boxBg;
    switch (typeCheckBox)
    {
        case EventType::TouchStart:
        case EventType::TouchEnter:
            boxBg = {COLOR_SILVER};
            break;
        case EventType::TouchEnd:
        default:
            boxBg = { (isEnabled() ? COLOR_WHITE : COLOR_SILVER) };
    }
    typeCheckBox = EventType::None;


    Point chPos = {int16_t(x2Left + p_checkbox::marginLeftRight) , int16_t(indentFrameTop - p_checkbox::boxWidth / 2 + 1)};
    if (chPos.x + p_checkbox::boxWidth < 0)
        return;
    uint16_t bxWidth, subzero;
    if (chPos.x < 0)
    {
        bxWidth = p_checkbox::boxWidth + chPos.x ;
        subzero =  -chPos.x;
    }
    else
    {
        bxWidth = p_checkbox::boxWidth;
        subzero = 0;
    }

    chPos.x += screenClient().x;
    chPos.y += screenClient().y;

    p_checkbox::drawCheckBox(chPos, boxBg, pMonitorDevice, bxWidth, subzero);
    if (checked && bxWidth > 2)
    {
        u_color chmarkClr;
        chmarkClr =  {isEnabled() ? COLOR_BLACK : COLOR_GRAY};
        p_checkbox::drawCheckmark(chPos, chmarkClr, pMonitorDevice,
                                  subzero < 3 ? 0 : subzero -  3);
    }
}

}
