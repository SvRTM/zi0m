/*
 * Copyright © 2016 Artem Smirnov
 * All right reserved.
 * Author: Artem Smirnov <msvrtm@gmail.com>
 * License: http://www.gnu.org/licenses/gpl.txt
 */

#ifndef SAMPLES_PC_LINUX_X11_H_
#define SAMPLES_PC_LINUX_X11_H_

#include "samples/pc/SimBase.h"

#include <X11/Xlib.h>
#undef None

using namespace zi0m;

struct RenderData final
{
    explicit RenderData() : exit(false) {}

    Display *dsp;
    GC ctx;
    Drawable win;
    Colormap cmap;

    bool exit;
};

class x11 final : public SimBase
{
    public:
        explicit x11();
        virtual ~x11();

    public:
        void exec() override;

    private:
        void createWindow();

    public:
        RenderData param;
};

#endif /* SAMPLES_PC_LINUX_X11_H_ */
