/*
 * x11.h
 *
 *  Created on: 11 марта 2016 г.
 *      Author: Artem.Smirnov
 */

#ifndef SRC_WIN32_TEST_X11_H_
#define SRC_WIN32_TEST_X11_H_

//#ifdef _linux_

#include <X11/Xlib.h>

class x11
{
    public:
        x11();
        virtual ~x11();

    public:
        void run();

        bool isBtPressed()
        {
            return btPressed;
        }

        Display *display;
        Window window;

        long eventmask;
        GC gc;
        Colormap colormap;
    private:
        volatile bool btPressed;

};

//#endif
#endif /* SRC_WIN32_TEST_X11_H_ */
