/*
 * EmuTouch.cpp
 *
 *  Created on: 27 янв. 2016 г.
 *      Author: Artem.Smirnov
 */

#include "EmuTouch.h"

const TypeTag EmuTouch::typeId = TypeTag::TOUCH_DEVICE;

void EmuTouch::setMessage(const Message msg)
{
    this->msg = msg;
}

bool EmuTouch::isPressed()
{
    return EventType::TouchStart == msg.touchEvent || EventType::TouchEnd == msg.touchEvent;
}

const Message EmuTouch::getMessage() const
{
    return msg;
}
