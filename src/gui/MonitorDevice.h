/*
 * MonitorDevice.h
 *
 *  Created on: 3 февр. 2016 г.
 *      Author: Artem.Smirnov
 */

#ifndef GUI_MONITORDEVICE_H_
#define GUI_MONITORDEVICE_H_

#include "common.h"
#include "font/ifont.h"

#include <string>

namespace zi0m
{
class MonitorDevice
{
    public:
        MonitorDevice();
        virtual ~MonitorDevice() {}

    public:
        virtual void setPoint(int16_t x, int16_t y, const u_color &color) = 0;
        virtual void fillRect(const Rect &rect, const u_color &color) = 0;
        virtual const uint16_t getWidth() const = 0;
        virtual const uint16_t getHight() const = 0;

        inline u_color alphaBlending(const u_color foreground,
                                     const u_color background) const
        {
            if (foreground.uc_color.A == 0xFFU)
                return foreground;

            float alpha = foreground.uc_color.A / 255.0f;
            float diff = 1.0f - alpha;

            u_color color;
            color.uc_color.B = foreground.uc_color.B * alpha + background.uc_color.B * diff;
            color.uc_color.G = foreground.uc_color.G * alpha + background.uc_color.G * diff;
            color.uc_color.R = foreground.uc_color.R * alpha + background.uc_color.R * diff;
            color.uc_color.A = 0xFFU;

            return color;
        }
};
}
#endif /* GUI_MONITORDEVICE_H_ */
