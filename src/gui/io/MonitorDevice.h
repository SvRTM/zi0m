/*
 * MonitorDevice.h
 *
 *  Created on: 3 февр. 2016 г.
 *      Author: Artem.Smirnov
 */

#ifndef IO_MONITORDEVICE_H_
#define IO_MONITORDEVICE_H_

#include "gui/common.h"
#include "gui/text/font/ifont.h"

#include <string>

namespace zi0m
{
class MonitorDevice
{
    public:
        MonitorDevice() {}
        virtual ~MonitorDevice() {}

    public:
        virtual void drawPoint(int16_t x, int16_t y, const u_color color) = 0;

        virtual void drawLine(int16_t x1, int16_t y1, int16_t x2, int16_t y2,
                              const u_color color) = 0;
        virtual void drawHLine(int16_t x, int16_t y, uint16_t width, const u_color color) = 0;
        virtual void drawVLine(int16_t x, int16_t y, uint16_t height, const u_color color) = 0;

        virtual void fillRect(const Rect &rect, const u_color color) = 0;

        virtual void drawCircle(int16_t cx, int16_t cy, uint16_t radius, const u_color color) = 0;
        virtual void drawCircle(int16_t cx, int16_t cy, uint16_t radius, int16_t dy,
                                const u_color color1, const u_color color2) = 0;
        virtual void fillCircle(int16_t x, int16_t y, uint16_t radius, const u_color color) = 0;


        virtual const uint16_t getWidth() const = 0;
        virtual const uint16_t getHight() const = 0;

#ifdef RGB888
        inline u_color alphaBlending(const u_color foreground, const u_color background) const
        {
            if (foreground.argb.A == 0xFFU)
                return foreground;

            const float alpha = foreground.argb.A / 255.0f;
            const float diff = 1.0f - alpha;

            u_color color;
            color.argb.B = foreground.argb.B * alpha + background.argb.B * diff;
            color.argb.G = foreground.argb.G * alpha + background.argb.G * diff;
            color.argb.R = foreground.argb.R * alpha + background.argb.R * diff;
            color.argb.A = 0xFFU;
#elif RGB565
        inline u_color alphaBlending(const u_color foreground, const u_color background,
                                     uint8_t A) const
        {
            if (A == 0xFFU)
                return foreground;

            const float alpha = A / 255.0f;
            const float diff = 1.0f - alpha;

            u_color color;
            color.rgb565.B = foreground.rgb565.B * alpha + background.rgb565.B * diff;
            color.rgb565.G = foreground.rgb565.G * alpha + background.rgb565.G * diff;
            color.rgb565.R = foreground.rgb565.R * alpha + background.rgb565.R * diff;
#endif
            return color;
        }
};
}
#endif /* IO_MONITORDEVICE_H_ */
