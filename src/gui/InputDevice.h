/*
 * InputDevice.h
 *
 *  Created on: 25 янв. 2016 г.
 *      Author: Artem.Smirnov
 */

#ifndef GUI_INPUTDEVICE_H_
#define GUI_INPUTDEVICE_H_

#include "common.h"

class InputDevice
{
    public:
        InputDevice();
        virtual ~InputDevice();

    public:
        virtual _MSG getMessage() const = 0;

};

#endif /* GUI_INPUTDEVICE_H_ */
