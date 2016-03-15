/*
 * x11.h
 *
 *  Created on: 11 марта 2016 г.
 *      Author: Artem.Smirnov
 */

#ifndef SRC_WIN32_TEST_X11_H_
#define SRC_WIN32_TEST_X11_H_

#include "gui/common.h"
#include "config.h"

#include <X11/Xlib.h>

struct RenderData
{
    RenderData() : exit(false) {}
    Display *d_;
    GC ctx;
    Drawable win;
    Colormap cmap;

    bool exit;
};

class x11
{

    public:
        x11();
        virtual ~x11();

    public:
        void cycle();

        bool isBtPressed()
        {
            return btPressed;
        }

        void createWindow();

    public:
        RenderData param;

    private:
        _MSG msg;
        volatile bool btPressed;
};

#endif /* SRC_WIN32_TEST_X11_H_ */
