/*
 * main.cpp
 *
 *  Created on: 22 янв. 2016 г.
 *      Author: Artem.Smirnov
 */

#include "win32.h"
#include "x11.h"
#include "Application.h"

#include <thread>

int main()
{
#ifdef WIN32
    init_for_win32();
    //while(true);
#elif LINUX

    //std::thread func_thread([&x]()->void{
    //    x.isBtPressed();
//    });
    XInitThreads();
    x11 x;

    // main cycle
    std::thread func_thread([x]()->void
            {
                Application app(&x);
                app.init();

                while (true)
                {
                    app.quantum();
                }
            });

    //func_thread.join();
    x.run();

#endif
}
