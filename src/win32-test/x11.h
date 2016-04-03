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
#include <unistd.h>

struct RenderData
{
    explicit RenderData() : exit(false) {}

    Display *dsp;
    GC ctx;
    Drawable win;
    Colormap cmap;

    bool exit;
};

class x11 final
{
    public:
        explicit x11();
        virtual ~x11();

    public:
        void exec();

    private:
        void createWindow();
        inline void clearMsg()
        {
            msg = {EventType::_None, {0, 0}};
        }

    public:
        RenderData param;

    private:
        _MSG msg;
};

#endif /* SRC_WIN32_TEST_X11_H_ */
