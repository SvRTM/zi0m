/*
 * EmuLcd.h
 *
 *  Created on: 31 янв. 2016 г.
 *      Author: Artem.Smirnov
 */

#ifndef X11_TEST_EMULCD_H_
#define X11_TEST_EMULCD_H_

#include "gui/io/MonitorDevice.h"
#include "config.h"

#ifdef PLATFORM_WIN32
    #include <windows.h>
#elif PLATFORM_LINUX
    #include "samples/pc/linux/x11.h"
    #include <X11/Xlib.h>
#endif

using namespace zi0m;

class EmuLcd: public MonitorDevice
{
    public:
#ifdef PLATFORM_WIN32
        explicit EmuLcd(HWND hWnd);
#elif PLATFORM_LINUX
        explicit EmuLcd(const RenderData *x11data);
#endif
        virtual ~EmuLcd() {}

    public:
        void setPoint(int16_t x, int16_t y, const u_color &color);
        void fillRect(const Rect &rect, const u_color &color);

        inline const uint16_t getWidth() const override;
        inline const uint16_t getHight() const override;

    private:
#ifdef PLATFORM_WIN32
        HWND hWnd;
#elif PLATFORM_LINUX
        const RenderData *x11data;
#endif
};

#endif /* X11_TEST_EMULCD_H_ */
