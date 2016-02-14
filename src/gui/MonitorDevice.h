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

        virtual void setPoint(int x, int y, const u_color &color) = 0;
        virtual void fillRect(const Rect &rect, const u_color &color) = 0;
        virtual uint16_t getWidth() = 0;
        virtual uint16_t getHight() = 0;
};

#endif /* GUI_MONITORDEVICE_H_ */
