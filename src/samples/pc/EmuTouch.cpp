/*
 * EmuTouch.cpp
 *
 *  Created on: 27 янв. 2016 г.
 *      Author: Artem.Smirnov
 */

#include "EmuTouch.h"

void EmuTouch::setMessage(Message msg)
{
    this->msg = msg;
}

bool EmuTouch::isPressed()
{
    return EventType::TouchStart == msg.touchEvent || EventType::TouchEnd == msg.touchEvent;
}

Message EmuTouch::getMessage() const
{
    return msg;
}
