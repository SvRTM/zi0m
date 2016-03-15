/*
 * MonitorDevice.cpp
 *
 *  Created on: 3 февр. 2016 г.
 *      Author: Artem.Smirnov
 */

#include "MonitorDevice.h"

MonitorDevice::MonitorDevice()
{
}
MonitorDevice::~MonitorDevice()
{
}

u_color MonitorDevice::RemoveAlpha(u_color foreground, u_color background)
{
    if (foreground.uc_color.A == 255)
        return foreground;

    auto alpha = foreground.uc_color.A / 255.0;
    auto diff = 1.0 - alpha;

    u_color color;
    color.uc_color.A = 255;
    color.uc_color.R = foreground.uc_color.R * alpha
                       + background.uc_color.R * diff;
    color.uc_color.G = foreground.uc_color.G * alpha
                       + background.uc_color.G * diff;
    color.uc_color.B = foreground.uc_color.B * alpha
                       + background.uc_color.B * diff;

    return color;
}
