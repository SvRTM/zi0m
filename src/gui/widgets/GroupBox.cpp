#include "GroupBox.h"


namespace zi0m
{

GroupBox::GroupBox(Point pos, Size size, Widget *const parent)
    : AbstractTextWidget(pos, size, Alignment(Alignment::VCenter | Alignment::Left), parent)
{
}

void GroupBox::p_setSize()
{
    calcPosition();
}
void GroupBox::p_setFont()
{
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

void GroupBox::event(const EventType type)
{
    if (!isEnabled())
        return;

    this->type = type;
}

/*
[y1Left]             [x2Left] -----------------------------------[x1Right] --- [y1Right]  <-- ..................................,
   ^---( i n d e n t )-^(textPadding)  {CheckBox}  {T E X T}^--------------^        <-- indentFrameTop -`
    |                        -----------------------------------------------                 |
    |                                                                                                 |
    |                                                                                                 |
    --------------------|-----------------------------------------------|---------------
*/
void GroupBox::calcPosition()
{
    if (text().length() == 0)
    {
        indentFrameTop = 0;
        return;
    }
    indentFrameTop = font().height / 2;

    TextCharacters::m_size.width = pxTextWidth();
    TextCharacters::m_size.height = font().height > size().height
                                    ? size().height : font().height;

    if (align & Alignment::Right)
    {
        x2Left = size().width - pxTextWidth() - (indent + textPadding);
        if (x2Left <= 0)
        {
            y1Left = font().height / 2;
            TextCharacters::m_size.width = size().width - (indent + textPadding);
        }
        else
            y1Left = 0;
        x1Right = size().width - indent;

        if (font().height >= size().height)
            isVisibleLeftLine = false;
        else
        {
            isWholeBottomLine = true;
            isVisibleLeftLine = true;
        }
    }
    else if (align & Alignment::HCenter)
    {
        x2Left = (size().width - pxTextWidth()) / 2 ;
        if (x2Left <= 0)
        {
            x1Right = size().width - 1 - 1;
            y1Right = y1Left = font().height / 2;
            TextCharacters::m_size.width = size().width;
        }
        else
            x1Right = size().width - x2Left + textPadding;

        if (font().height >= size().height)
            isWholeBottomLine = false;
        else
            isWholeBottomLine = true;
    }
    else // if (align & Alignment::Left)
    {
        x2Left = indent;
        x1Right = indent + textPadding + pxTextWidth();
        if (x1Right >= size().width)
        {
            x1Right = size().width - 1 - 1;
            y1Right = font().height / 2;
            TextCharacters::m_size.width = size().width - (indent + textPadding);
        }
        else
            y1Right = 0;

        if (font().height >= size().height)
            isVisibleRightLine = false;
        else
        {
            isWholeBottomLine = true;
            isVisibleRightLine = true;
        }
    }
    TextCharacters::m_pos.x = x2Left <= 0 ? 0 :  x2Left + textPadding;

    TextCharacters::updateAbsPosition(absolutePos);
}

void GroupBox::paint(MonitorDevice *const pMonitorDevice)
{
    pMonitorDevice->fillRect(screen(), background());
    //u_color colorTL, colorBR;

    Point chPos = {0, indentFrameTop};
    chPos.x += screen().x;
    chPos.y += screen().y;

    if (x2Left > 0)
    {
        //top-left
        pMonitorDevice->drawLine(chPos.x , chPos.y, chPos.x + x2Left , chPos.y, {COLOR_GRAY});
        pMonitorDevice->drawLine(chPos.x , chPos.y + 1, chPos.x + x2Left , chPos.y + 1, {COLOR_WHITE});
    }
    if (y1Right == 0)
    {
        //top-right
        pMonitorDevice->drawLine(chPos.x + x1Right , chPos.y,
                                 chPos.x + size().width - 1 - 1, chPos.y, {COLOR_GRAY});
        pMonitorDevice->drawLine(chPos.x  + x1Right, chPos.y + 1,
                                 chPos.x + size().width - 1 - 1 - 1, chPos.y + 1, {COLOR_WHITE});
    }

    if (isVisibleLeftLine)
    {
        // left
        pMonitorDevice->drawLine(chPos.x, chPos.y + y1Left, chPos.x,
                                 chPos.y + size().height - indentFrameTop - 1 - 1, {COLOR_GRAY});
        pMonitorDevice->drawLine(chPos.x + 1, chPos.y + 1 + y1Left, chPos.x + 1,
                                 chPos.y + 1 + size().height - indentFrameTop - 1 - 1 - 1, {COLOR_WHITE});
    }

    if (isVisibleRightLine)
    {
        // right
        pMonitorDevice->drawLine(chPos.x + size().width - 1, chPos.y + y1Right,
                                 chPos.x + size().width - 1, chPos.y + size().height - indentFrameTop - 1 - 1,
        {COLOR_WHITE});
        pMonitorDevice->drawLine(chPos.x + size().width - 1 - 1, chPos.y + y1Right,
                                 chPos.x + size().width - 1 - 1, chPos.y + size().height - indentFrameTop - 1 - 1,
        {COLOR_GRAY});
    }

    if (isVisibleLeftLine && isVisibleRightLine)
    {
        // bottom
        uint16_t x2 = isWholeBottomLine ? size().width - 1 - 1 : x2Left;
        pMonitorDevice->drawLine(chPos.x, chPos.y + size().height - indentFrameTop - 1 - 1,
                                 chPos.x + x2 , chPos.y + size().height - indentFrameTop - 1 - 1,
        {COLOR_GRAY});
        pMonitorDevice->drawLine(chPos.x, chPos.y + size().height - indentFrameTop - 1 ,
                                 chPos.x + x2, chPos.y + size().height - indentFrameTop - 1,
        {COLOR_WHITE});

        if ( !isWholeBottomLine)
        {
            pMonitorDevice->drawLine(chPos.x + x1Right,
                                     chPos.y + size().height - indentFrameTop - 1 - 1,
                                     chPos.x + size().width - 1 - 1, chPos.y + size().height - indentFrameTop - 1 - 1,
            {COLOR_GRAY});

            pMonitorDevice->drawLine(chPos.x + x1Right,
                                     chPos.y + size().height - indentFrameTop - 1 ,
                                     chPos.x + size().width - 1 , chPos.y + size().height - indentFrameTop - 1,
            {COLOR_WHITE});
        }
    }

    drawText(pMonitorDevice);
}

}
