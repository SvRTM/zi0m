/*
 * x11.h
 *
 *  Created on: 11 марта 2016 г.
 *      Author: Artem.Smirnov
 */

#ifndef SRC_WIN32_TEST_X11_H_
#define SRC_WIN32_TEST_X11_H_

#include "gui/common.h"

#include <X11/Xlib.h>
#undef None
#include <unistd.h>

using namespace zi0m;

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
        inline void clearMessage()
        {
            msg = {EventType::None, 0};
        }

    public:
        RenderData param;

    private:
        Message msg = {EventType::None, 0};
};

#endif /* SRC_WIN32_TEST_X11_H_ */
