/*
 * EmuTouch.cpp
 *
 *  Created on: 27 янв. 2016 г.
 *      Author: Artem.Smirnov
 */

#include "EmuTouch.h"

EmuTouch::EmuTouch()
{
}

EmuTouch::~EmuTouch()
{
}
void EmuTouch::setMessage(_MSG msg)
{
    this->msg = msg;
}

bool EmuTouch::isPressed()
{
    return Message::TouchDown == msg.message || Message::TouchUp == msg.message;
}

_MSG EmuTouch::getMessage() const
{
    return msg;
}
