/*
 * Copyright © 2016 Artem Smirnov
 * All right reserved.
 * Author: Artem Smirnov <msvrtm@gmail.com>
 * License: http://www.gnu.org/licenses/gpl.txt
 */

#ifndef SAMPLES_PC_EMUTOUCH_H_
#define SAMPLES_PC_EMUTOUCH_H_

#include "gui/io/InputDevice.h"

using namespace zi0m;

class EmuTouch final : public InputDevice
{
    public:
        EmuTouch() = default;
        virtual ~EmuTouch() = default;
    private:
        EmuTouch(const EmuTouch &) = delete;
        EmuTouch &operator=(const EmuTouch &) = delete;

    public:
        inline TypeTag typeID() const
        {
            return typeId;
        }

        void setMessage(const Message msg);
        bool isPressed();
        const Message getMessage() const override;

    private:
        static const TypeTag typeId;

        Message msg;
};

#endif /* SAMPLES_PC_EMUTOUCH_H_ */
