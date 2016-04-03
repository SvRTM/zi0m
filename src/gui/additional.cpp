#include "additional.h"

#include "font/Terminus_11pt_Regular.h"

Additional::Additional(u_color bg) :
    pFont(&FONT(Terminus_11pt_Regular)),
    m_background(bg), visible(true)
{
}

void Additional::setBackground(const u_color bg)
{
    m_background = bg;
}

void Additional::setVisible(bool visible)
{
    this->visible = visible;
}
