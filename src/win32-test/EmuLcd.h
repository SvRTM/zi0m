/*
 * EmuLcd.h
 *
 *  Created on: 31 янв. 2016 г.
 *      Author: Artem.Smirnov
 */

#ifndef WIN32_TEST_EMULCD_H_
#define WIN32_TEST_EMULCD_H_

#include "../gui/MonitorDevice.h"

#ifdef WIN32
#include <windows.h>
#elif LINUX
#include <X11/Xlib.h>
#endif
class EmuLcd: public MonitorDevice
{
    public:
#ifdef WIN32
        EmuLcd(HWND hWnd);
#else
        EmuLcd(Display *display, Drawable window, GC gc, Colormap cmap);
#endif
        virtual ~EmuLcd();

        void onPaint();

        void setPoint(int x, int y, const u_color &color);
        void fillRect(const Rect &rect, const u_color &color);

        inline uint16_t getWidth() override;
        inline uint16_t getHight() override;

    private:
#ifdef WIN32
        HWND hWnd;
#else
        Display *display;
        Drawable window;
        GC gc;
        Colormap cmap;
#endif
};

#endif /* WIN32_TEST_EMULCD_H_ */
