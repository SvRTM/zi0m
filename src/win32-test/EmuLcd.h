/*
 * EmuLcd.h
 *
 *  Created on: 31 янв. 2016 г.
 *      Author: Artem.Smirnov
 */

#ifndef WIN32_TEST_EMULCD_H_
#define WIN32_TEST_EMULCD_H_

#include "../gui/MonitorDevice.h"
#include <windows.h>

class EmuLcd: public MonitorDevice
{
    public:
        EmuLcd(HWND hWnd);
        virtual ~EmuLcd();

        void onPaint();

        void setPoint(int x, int y, const u_color &color);
        void fillRect(const Rect &rect, const u_color &color);

        inline uint16_t getWidth() override;
        inline uint16_t getHight() override;

    private:
        HWND hWnd;
};

#endif /* WIN32_TEST_EMULCD_H_ */
