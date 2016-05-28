/*
 * Copyright © 2016 Artem Smirnov
 * All right reserved.
 * Author: Artem Smirnov <msvrtm@gmail.com>
 * License: http://www.gnu.org/licenses/gpl.txt
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
