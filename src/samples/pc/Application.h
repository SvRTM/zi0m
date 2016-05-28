/*
 * Copyright © 2016 Artem Smirnov
 * All right reserved.
 * Author: Artem Smirnov <msvrtm@gmail.com>
 * License: http://www.gnu.org/licenses/gpl.txt
 */

#ifndef SAMPLES_PC_APPLICATION_H_
#define SAMPLES_PC_APPLICATION_H_

#include "gui/kernel/ApplicationBase.h"
#include "samples/MainWindow.h"
#include "config.h"

#ifdef PLATFORM_WIN32
#include <windows.h>
#undef min
#elif PLATFORM_LINUX
#include "samples/pc/linux/x11.h"
#endif

using namespace zi0m;

class Application final : public ApplicationBase
{
    public:
#ifdef PLATFORM_WIN32
        explicit Application();
        void init(HWND _hWnd);
#elif PLATFORM_LINUX
        explicit Application(const x11 *x);
        void init();
#endif
        virtual ~Application() = default;

    public:
        void setMessage(const Message msg);

    private:
#if PLATFORM_LINUX
        const x11 *m_pX11;
#endif
};

#endif /* SAMPLES_PC_APPLICATION_H_ */
