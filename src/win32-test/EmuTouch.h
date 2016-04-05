/*
 * EmuTouch.h
 *
 *  Created on: 27 янв. 2016 г.
 *      Author: Artem.Smirnov
 */

#ifndef WIN32_TEST_EMUTOUCH_H_
#define WIN32_TEST_EMUTOUCH_H_

#include "../gui/InputDevice.h"

using namespace zi0m;

class EmuTouch final : public InputDevice
{
    public:
        EmuTouch();
        virtual ~EmuTouch();

    public:
        void setMessage(_MSG msg);
        bool isPressed();
        _MSG getMessage() const override;

    private:
        _MSG msg;
};

#endif /* WIN32_TEST_EMUTOUCH_H_ */
