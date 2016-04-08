#include "additional.h"

#include "gui/text/font/Terminus_11pt_Regular.h"

namespace zi0m
{

Additional::Additional(u_color bg) :
    pFont(&FONT(Terminus_11pt_Regular)),
    m_background(bg)
{
}

void Additional::setBackground(const u_color bg)
{
    m_background = bg;
}

void Additional::setEnabled(bool enabled)
{
    this->enabled = enabled;
    refresh();
}

}
