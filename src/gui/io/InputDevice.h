/*
 * Copyright © 2016 Artem Smirnov
 * All right reserved.
 * Author: Artem Smirnov <msvrtm@gmail.com>
 * License: http://www.gnu.org/licenses/gpl.txt
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
