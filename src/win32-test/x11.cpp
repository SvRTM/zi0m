/*
 * x11.cpp
 *
 *  Created on: 11 марта 2016 г.
 *      Author: Artem.Smirnov
 */

#include "x11.h"
#include "Application.h"

#include <stdio.h>
#include <cstring>
#include <unistd.h>
#include <signal.h>
#include <errno.h>
#include <limits>
#include <cmath>
#include <climits>

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


x11::x11()
{
    if (!(param.d_ = XOpenDisplay(nullptr)))
    {
        printf("No X11 display, errno = %d, %s", errno, strerror(errno));
        fflush(stdout);
        Panic("X11 error !");
    }
}
x11::~x11()
{
    //XUnloadFont(dpy, font_info->fid);

    XUnmapWindow(param.d_, param.win);
    XDestroyWindow(param.d_, param.win);
    XCloseDisplay(param.d_);
}

void x11::createWindow()
{
    int screen = DefaultScreen(param.d_);
    Window root = RootWindow(param.d_, screen);

    Atom wmDelete = XInternAtom(param.d_, "WM_DELETE_WINDOW", false);

    long bgcolor = WhitePixel(param.d_, screen);

    int depth =  DefaultDepth(param.d_, screen);
    Visual *visual = DefaultVisual(param.d_, screen);
    XSetWindowAttributes attributes;
    attributes.background_pixel = bgcolor;
    param.win = XCreateWindow(param.d_, root, 0, 0, 320, 240, 0, depth,
                              InputOutput, visual
                              , CWBackPixel,
                              &attributes);

    param.cmap = DefaultColormap(param.d_, screen);
    param.ctx =  DefaultGC(param.d_, screen);

    long eventmask = ButtonPressMask | ButtonReleaseMask | ExposureMask
                     | KeyPressMask
                     | StructureNotifyMask | PropertyChangeMask | VisibilityChangeMask
                     | FocusChangeMask;
    XSelectInput(param.d_, param.win, eventmask);
    XSetWMProtocols(param.d_, param.win, &wmDelete, true);

    cycle();
}

void x11::cycle()
{
    Application app(this);
    app.init();

    XMapWindow(param.d_, param.win);

    while (!param.exit)
    {
        XEvent event;
       if (XPending(param.d_))
        {
            XNextEvent(param.d_, &event);
            switch (event.type)
            {
                case Expose:
                    msg.message = Message::_None;
                    /* Unless this is the last contiguous expose,
                     * don't draw the window */
                    printf("Expose!\n");
                    //XClearWindow(display, window);
                    break;
                case ConfigureNotify:
                    msg.message = Message::_None;
                    /* Window has been resized; change width and height
                     * to send to place_text and place_graphics in
                     * next Expose */
                    printf("Window moved or resized!\n");
                    break;
                case ButtonPress:
                {
                    msg.message = Message::TouchDown;
                    int pointx = event.xbutton.x;
                    int pointy = event.xbutton.y;
                    msg.pt = Point(pointx, pointy);
                    printf("ButtonPress! %d:%d\n", pointx, pointy);
                    break;
                }
                case ButtonRelease:
                {
                    msg.message = Message::TouchUp;
                    int pointx = event.xbutton.x;
                    int pointy = event.xbutton.y;
                    msg.pt = Point(pointx, pointy);
                    printf("Button released : %d  %d:%d\n", event.xbutton.button - 1, pointx,
                           pointy);
                    break;
                }
                case KeyPress:
                    msg.message = Message::_None;
                    fprintf(stdout, "KeyPress: %d\n", event.type);
                    break;
                case ClientMessage:
                    msg.message = Message::_None;
                    // TODO Should check here for other client message types -
                    // however as the only protocol registered above is WM_DELETE_WINDOW
                    // it is safe for this small example.

                    param.exit = true;
                    break;
                case DestroyNotify:
                    msg.message = Message::_None;
                    printf("Window killed!\n");
                    break;
                default:
                    msg.message = Message::_None;
                    fprintf(stderr, "Unexpected event: %d\n", event.type);
            }
        }
        app.setMessage(msg);
        usleep(16000);
        app.quantum();

        msg.message = Message::_None;
        msg.pt = Point();
    }
}

