/*
 * Copyright © 2016 Artem Smirnov
 * All right reserved.
 * Author: Artem Smirnov <msvrtm@gmail.com>
 * License: http://www.gnu.org/licenses/gpl.txt
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
    Win32 w;
#elif PLATFORM_LINUX
    x11 w;
#endif
    w.exec();
}
