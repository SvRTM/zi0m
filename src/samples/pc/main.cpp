/*
 * main.cpp
 *
 *  Created on: 22 янв. 2016 г.
 *      Author: Artem.Smirnov
 */

#include "config.h"

#ifdef PLATFORM_WIN32
    #include "samples/pc/win/win32.h"
#elif PLATFORM_LINUX
    #include "samples/pc/linux/x11.h"
#endif

int main()
{
#ifdef PLATFORM_WIN32
    init_for_win32();
#elif PLATFORM_LINUX
    x11 x;
    x.exec();
#endif
}
