#include "additional.h"

#include "font/Terminus_11pt_Regular.h"

Additional::Additional() : pFont(&Singleton<Terminus_11pt_Regular>::instance()),
    m_background({0x00E8F6FAU}), visible(true)
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
