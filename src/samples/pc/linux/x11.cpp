/*
 * x11.cpp
 *
 *  Created on: 11 марта 2016 г.
 *      Author: Artem.Smirnov
 */

#include "x11.h"
#include "samples/pc/Application.h"

#include <stdio.h>
#include <cstring>

#include <signal.h>
#include <errno.h>

void  Panic(const char *msg)
{
#ifdef PLATFORM_POSIX
    signal(SIGILL, SIG_DFL);
    signal(SIGSEGV, SIG_DFL);
    signal(SIGBUS, SIG_DFL);
    signal(SIGFPE, SIG_DFL);
#endif

#ifdef PLATFORM_WIN32
#   ifdef __NOASSEMBLY__
#       if defined(PLATFORM_WINCE) || defined(WIN64)
    DebugBreak();
#       endif
#   else
#       if defined(_DEBUG) && defined(CPU_X86)
#           ifdef COMPILER_MSC
    _asm int 3
#           endif
#           ifdef COMPILER_GCC
    asm("int $3");
#           endif
#       endif
#   endif
#else
#endif
#ifdef _DEBUG
    __BREAK__;
#endif
    //abort();
}


x11::x11() : msg({EventType::_None, {0, 0}})
{
    if (!(param.dsp = XOpenDisplay(nullptr)))
    {
        printf("No X11 display, errno = %d, %s", errno, strerror(errno));
        fflush(stdout);
        Panic("X11 error !");
    }

    createWindow();
}
x11::~x11()
{
    XUnmapWindow(param.dsp, param.win);
    XDestroyWindow(param.dsp, param.win);
    XCloseDisplay(param.dsp);
}

void x11::createWindow()
{
    int screen = DefaultScreen(param.dsp);
    Window root = RootWindow(param.dsp, screen);

    Atom wmDelete = XInternAtom(param.dsp, "WM_DELETE_WINDOW", false);

    long bgcolor = WhitePixel(param.dsp, screen);

    int depth =  DefaultDepth(param.dsp, screen);
    Visual *visual = DefaultVisual(param.dsp, screen);
    XSetWindowAttributes attributes;
    attributes.background_pixel = bgcolor;
    param.win = XCreateWindow(param.dsp, root,
                              0, 0, 320, 240, 0, depth,
                              InputOutput, visual,
                              CWBackPixel, &attributes);

    param.cmap = DefaultColormap(param.dsp, screen);
    param.ctx =  DefaultGC(param.dsp, screen);

    long eventmask = PointerMotionMask | ButtonPressMask | ButtonReleaseMask
                     | ExposureMask
                     | KeyPressMask
                     | StructureNotifyMask | PropertyChangeMask | VisibilityChangeMask
                     | FocusChangeMask;
    XSelectInput(param.dsp, param.win, eventmask);
    XSetWMProtocols(param.dsp, param.win, &wmDelete, true);
}

void x11::exec()
{
    Application app(this);
    app.init();

    XMapWindow(param.dsp, param.win);

    bool isBtnPressed = false;
    while (!param.exit)
    {
        if (XPending(param.dsp))
        {
            XEvent event;
            XNextEvent(param.dsp, &event);
            switch (event.type)
            {
                case Expose:
                    /* Unless this is the last contiguous expose, don't draw the window */
                    if (event.xexpose.count == 0)
                        printf("Expose!\n");
                    break;
                case ConfigureNotify:
                    /* Window has been resized; change width and height
                     * to send to place_text and place_graphics in
                     * next Expose */
                    printf("Window moved or resized!\n");
                    break;

                case MotionNotify:
                {
                    if (isBtnPressed)
                    {
                        int pointx = event.xmotion.x;
                        int pointy = event.xmotion.y;
                        printf("  Touch move    : [%d, %d]\n", pointx, pointy);

                        msg.touchEvent = EventType::TouchStart;
                        msg.pt = Point(pointx, pointy);
                    }
                    break;
                }
                case ButtonPress:
                {
                    isBtnPressed = true;

                    int pointx = event.xbutton.x;
                    int pointy = event.xbutton.y;
                    printf("Touch start     : [%d, %d]\n", pointx, pointy);

                    msg.touchEvent = EventType::TouchStart;
                    msg.pt = Point(pointx, pointy);
                    break;
                }
                case ButtonRelease:
                {
                    isBtnPressed = false;

                    int pointx = event.xbutton.x;
                    int pointy = event.xbutton.y;
                    printf("Touch end       : [%d, %d]\n\n", pointx, pointy);

                    msg.touchEvent = EventType::TouchEnd;
                    msg.pt = Point(pointx, pointy);
                    break;
                }
                case KeyPress:
                    printf("KeyPress: %d\n", event.type);
                    break;
                case ClientMessage:
                    // TODO Should check here for other client message types -
                    // however as the only protocol registered above is WM_DELETE_WINDOW
                    // it is safe for this small example.
                    printf("WM_DELETE_WINDOW!\n");
                    param.exit = true;
                    break;
                case DestroyNotify:
                    printf("Window killed!\n");
                    break;
                default:
                    fprintf(stderr, "Unexpected event: %d\n", event.type);
            }
        }
        usleep(16000);

        app.setMessage(msg);
        app.quantum();

        clearMsg();
    }
}

