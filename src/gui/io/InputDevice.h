/*
 * InputDevice.h
 *
 *  Created on: 25 янв. 2016 г.
 *      Author: Artem.Smirnov
 */

#ifndef IO_INPUTDEVICE_H_
#define IO_INPUTDEVICE_H_

#include "gui/common.h"

namespace zi0m
{
class InputDevice
{
    public:
        InputDevice() = default;
        virtual ~InputDevice() = default;

    public:
        virtual TypeTag typeID() const = 0;
        virtual const Message getMessage() const = 0;
};
}
#endif /* IO_INPUTDEVICE_H_ */
