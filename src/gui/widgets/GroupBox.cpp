#include "GroupBox.h"


namespace zi0m
{

GroupBox::GroupBox(Point pos, Size size, Widget *const parent)
    : AbstractTextWidget(pos, size, Alignment(Alignment::VCenter | Alignment::Left), parent)
{
    setBackground({COLOR_GREEN});
    TextCharacters::m_pos.y = 0;
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

void GroupBox::setCheckable(bool checkable)
{
    this->checkable = checkable;
    if (checkable)
    {
        //        pCheckBox = new CheckBox(0, this);
        //        pCheckBox->setState(CheckBox::State::Checked);
        //        pCheckBox->setBackground({COLOR_GRAYL});

        //        pCheckBox->setText(TextCharacters::text());
        //        TextCharacters::setText(std::u16string());
    }
    //else if (pCheckBox)
    {
        //        TextCharacters::setText(pCheckBox->text());

        //        delete pCheckBox;
        //        pCheckBox = nullptr;
    }
    calcPosition();
}

void GroupBox::setChecked(bool checked)
{
    this->checked = checked;
}

void GroupBox::setAlignment(Alignment align)
{
    //     TextCharacters::setAlignment(align);
    alignCenter = align & Alignment::HCenter;
    TextCharacters::setAlignment(align & Alignment::HCenter ? Alignment((
                                     align ^ Alignment::HCenter) | Alignment::Left) : align);
}

/*
[y1Left]             [x2Left] --------------------------------------------------[x1Right] --- [y1Right]  <-- ..................................,
   ^---( i n d e n t )-^{ marg. CheckBox marg.} (textPadding) {T E X T}^--------------^         <-- indentFrameTop -`
    |                        --------------------------------------------------------------                 |
    |                                                                                                                   |
    |                                                                                                                   |
    --------------------|-------------------------------------------------------------|----------------
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
                                    ? size().height : (
                                        checkable && font().height < boxWidth
                                        ? boxWidth : font().height);

    if (align & Alignment::Right)
    {
        if (checkable)
            x2Left = size().width - (marginLeftRight + boxWidth + marginLeftRight) - textPadding -
                     pxTextWidth() - indent;
        else
            x2Left = size().width - textPadding - pxTextWidth() - indent;
        if (x2Left <= 0)
        {
            y1Left = font().height / 2;
            if (checkable)
                if (size().width - indent < pxTextWidth())
                    TextCharacters::m_size.width = size().width - indent;
                else
                    TextCharacters::m_size.width = size().width - x2Left - (marginLeftRight + boxWidth +
                                                   marginLeftRight) - textPadding - indent;
            else
                TextCharacters::m_size.width = size().width - textPadding - indent;
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
    //else if (align & Alignment::HCenter)
    else if (alignCenter)
    {
        if (checkable)
            x2Left = (size().width - (marginLeftRight + boxWidth + marginLeftRight) - textPadding -
                      pxTextWidth()) / 2;
        else
            x2Left = (size().width - textPadding - pxTextWidth()) / 2;
        if (x2Left <= 0)
        {
            //x1Right = size().width - 1 - 1;
            y1Right = y1Left = font().height / 2;
            if (checkable)
            {
                TextCharacters::m_size.width = size().width - (marginLeftRight + x2Left + boxWidth +
                                               marginLeftRight) - textPadding;
                if (TextCharacters::m_size.width > size().width)
                    TextCharacters::m_size.width = size().width;
            }
            else
                TextCharacters::m_size.width = size().width;
        }
        else
        {
            if (x2Left <= marginLeftRight)
                y1Right = y1Left = font().height / 2;
            else
                y1Right = y1Left = 0;
            x1Right = size().width - x2Left;
        }

        if (font().height >= size().height)
        {
            isWholeBottomLine = false;
            isVisibleRightLine = false;
            isVisibleLeftLine = false;
        }
        else
        {
            isWholeBottomLine = true;
            isVisibleRightLine = true;
            isVisibleLeftLine = true;
        }
    }
    else // if (align & Alignment::Left)
    {
        x2Left = indent;
        if (checkable)
            x1Right = indent + (marginLeftRight + boxWidth + marginLeftRight) + textPadding +
                      pxTextWidth();
        else
            x1Right = indent + textPadding + pxTextWidth();
        if (x1Right >= size().width - 2)
        {
            x1Right = size().width - 1 - 1;
            y1Right = font().height / 2;
            if (checkable)
                TextCharacters::m_size.width = size().width - indent - (marginLeftRight + boxWidth +
                                               marginLeftRight) - textPadding;
            else
                TextCharacters::m_size.width = size().width - indent - textPadding;
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

    if (checkable)
    {
        TextCharacters::m_pos.x = x2Left + marginLeftRight + boxWidth + marginLeftRight +
                                  textPadding;
        if (TextCharacters::m_pos.x < 0)
            TextCharacters::m_pos.x = 0;
    }
    else
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

    if (x2Left > 1)
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
        //if (TextCharacters::m_size.width >= )
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
                                 chPos.x + size().width - 1, chPos.y + size().height - indentFrameTop - 1,
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

    drawText(pMonitorDevice, alignCenter && x2Left < 0 ? x2Left : 0);
    if (checkable)
        checkBox(pMonitorDevice);
}

void GroupBox::checkBox(MonitorDevice *const pMonitorDevice)
{
    u_color boxBg = {COLOR_WHITE};

    Point chPos = {int16_t(x2Left + marginLeftRight) , int16_t(indentFrameTop - boxWidth / 2 + 1)};
    if (chPos.x + boxWidth < 0)
        return;
    uint16_t w, xd;
    if (chPos.x < 0)
    {
        w = boxWidth + chPos.x ; //abs(chPos.x) +2 * borderWidth ;
        //chPos.x = -2 * borderWidth;
        xd =  abs(chPos.x);//2 * borderWidth;
    }
    else
    {
        //chPos.x = 0;//chPos.x+2 * borderWidth;
        w = boxWidth - 4 * borderWidth;
        xd = 0;
    }

    chPos.x += screen().x;
    chPos.y += screen().y;

    if (w > 2)
        pMonitorDevice->fillRect({int16_t(chPos.x + 2 * borderWidth + (xd == 0 ? 0 : xd - 2 * borderWidth) ), int16_t(chPos.y + 2 * borderWidth),
                                  uint16_t(w), uint16_t(boxWidth - 4 * borderWidth)
                                 }, boxBg);

    //    if (State::Unchecked != state)
    //    {
    //        u_color chmarkClr;
    //        chmarkClr =  {isEnabled()
    //                      ? (State::PartiallyChecked == state
    //                         ? COLOR_GRAY_ARSENIC : COLOR_BLACK)
    //                      : (State::PartiallyChecked == state
    //                         ? COLOR_GRAYL : COLOR_GRAY)
    //                     };
    //        drawCheckmark(chPos, chmarkClr, pMonitorDevice );
    //    }

    u_color colorTL = {COLOR_GRAY};
    u_color colorTL2({COLOR_GRAYD});
    if (chPos.x >= absolutePos.x)
    {
        // left
        pMonitorDevice->fillRect({chPos.x, chPos.y, borderWidth, uint16_t(boxWidth - borderWidth)
                                 }, colorTL);
        // left
        pMonitorDevice->fillRect({int16_t(chPos.x + borderWidth), int16_t(chPos.y + borderWidth),
                                  borderWidth, uint16_t(boxWidth - 3 * borderWidth)
                                 }, colorTL2);
    }

    //if (boxWidth - borderWidth - xd >0)

    if (w > 1)
        // top
        pMonitorDevice->fillRect({int16_t(chPos.x + xd), chPos.y, uint16_t(boxWidth - borderWidth - xd), borderWidth
                                 }, colorTL);
    if (w > 2)
        // top
        pMonitorDevice->fillRect({int16_t(chPos.x + (xd == 0 ? 2 * borderWidth : xd)), int16_t(chPos.y + borderWidth),
                                  uint16_t(boxWidth - 2 * borderWidth - (xd == 0 ? 2 * borderWidth : xd)), borderWidth
                                 }, colorTL2);

    u_color colorBR = {COLOR_WHITE};
    u_color colorBR2 = {COLOR_SILVER};
    if (w > 0)
        // right
        pMonitorDevice->fillRect({int16_t(chPos.x + boxWidth - borderWidth), chPos.y,
                                  borderWidth, boxWidth
                                 }, colorBR);
    if (w > 1)
        // right
        pMonitorDevice->fillRect({int16_t(chPos.x + boxWidth - 2 * borderWidth), int16_t(chPos.y + borderWidth),
                                  borderWidth, uint16_t(boxWidth - 2 * borderWidth)
                                 }, colorBR2);
    if (w > 1)
        // bottom
        pMonitorDevice->fillRect({int16_t(chPos.x + (xd == 0 ? 0 : xd)), int16_t(chPos.y + boxWidth - borderWidth),
                                  uint16_t(boxWidth - borderWidth - (xd == 0 ? 0 : xd)), borderWidth
                                 }, colorBR);
    if (w > 2)
        // bottom
        pMonitorDevice->fillRect({int16_t(chPos.x + (xd == 0 ? borderWidth : xd)), int16_t(chPos.y + boxWidth - 2 * borderWidth),
                                  uint16_t(boxWidth - (xd == 0 ? 3 * borderWidth : xd + borderWidth)), borderWidth
                                 }, colorBR2);
}

}
