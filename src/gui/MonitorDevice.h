/*
 * MonitorDevice.h
 *
 *  Created on: 3 февр. 2016 г.
 *      Author: Artem.Smirnov
 */

#ifndef GUI_MONITORDEVICE_H_
#define GUI_MONITORDEVICE_H_

#include "common.h"

class MonitorDevice
{
    public:
        MonitorDevice();
        virtual ~MonitorDevice();

    public:
        virtual void setPoint(int16_t x, int16_t y, const u_color &color) = 0;
        virtual void fillRect(const Rect &rect, const u_color &color) = 0;
        virtual const uint16_t getWidth() const = 0;
        virtual const uint16_t getHight() const = 0;

        u_color RemoveAlpha(u_color foreground, u_color background);
};

#endif /* GUI_MONITORDEVICE_H_ */
