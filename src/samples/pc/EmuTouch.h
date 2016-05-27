/*
 * EmuTouch.h
 *
 *  Created on: 27 янв. 2016 г.
 *      Author: Artem.Smirnov
 */

#ifndef WIN32_TEST_EMUTOUCH_H_
#define WIN32_TEST_EMUTOUCH_H_

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

#endif /* WIN32_TEST_EMUTOUCH_H_ */
