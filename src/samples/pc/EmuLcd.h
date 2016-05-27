/*
 * EmuLcd.h
 *
 *  Created on: 31 янв. 2016 г.
 *      Author: Artem.Smirnov
 */

#ifndef X11_TEST_EMULCD_H_
#define X11_TEST_EMULCD_H_

#include "gui/io/MonitorDevice.h"

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
        virtual ~EmuLcd() = default;
    private:
        EmuLcd(const EmuLcd &) = delete;
        EmuLcd &operator=(const EmuLcd &) = delete;

    public:
        void drawPoint(int16_t x, int16_t y, const u_color color) override;

        inline void drawLine(int16_t x1, int16_t y1, int16_t x2, int16_t y2,
                             const u_color color) override;
        inline void drawHLine(int16_t x, int16_t y, uint16_t width,
                              const u_color color) override;
        inline void drawVLine(int16_t x, int16_t y, uint16_t height,
                              const u_color color) override;

        void fillRect(const Rect &rect, const u_color color) override;

        void fillCircle(int16_t cx, int16_t cy, uint16_t radius, const u_color color) override;
        void drawCircle(int16_t cx, int16_t cy, uint16_t radius, const u_color color) override;
        void drawCircle(int16_t cx, int16_t cy, uint16_t radius, int16_t dy,
                        const u_color color1, const u_color color2) override;


        inline uint16_t getWidth() const override
        {
            return 320;
        }
        inline uint16_t getHight() const override
        {
            return 240;
        }

    private:
#ifdef PLATFORM_WIN32
        COLORREF toColorRef(const u_color color);
#elif PLATFORM_LINUX
        void setColor(const u_color color);
#endif

        void p_drawLine(int16_t x1, int16_t y1, int16_t x2, int16_t y2
#ifdef PLATFORM_WIN32
                        , const u_color color
#endif
                       );

    private:
#ifdef PLATFORM_WIN32
        HWND hWnd;

#ifdef RGB565
        /** Used information from the website: www.tune-it.ru/web/il/home/-/blogs/36120 */
        static const uint8_t table5[32];
        static const uint8_t table6[64];
#endif
#elif PLATFORM_LINUX
        const RenderData *x11data;
#endif
};

#endif /* X11_TEST_EMULCD_H_ */
