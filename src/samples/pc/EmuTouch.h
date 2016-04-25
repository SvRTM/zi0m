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
        virtual ~EmuTouch() {}

    public:
        void setMessage(Message msg);
        bool isPressed();
        Message getMessage() const override;

    private:
        Message msg;
};

#endif /* WIN32_TEST_EMUTOUCH_H_ */
