/*
 * x11.cpp
 *
 *  Created on: 11 марта 2016 г.
 *      Author: Artem.Smirnov
 */

#include "x11.h"
#include "samples/pc/Application.h"

#include <cstring>
#include <unistd.h>


x11::x11()
{
    if (!(param.dsp = XOpenDisplay(nullptr)))
        Panic("No X11 display, errno = %d, %s", errno, strerror(errno));

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

    int depth = DefaultDepth(param.dsp, screen);
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
                     //| ExposureMask
                     //| KeyPressMask
                     //| StructureNotifyMask | PropertyChangeMask | VisibilityChangeMask
                     //| FocusChangeMask
                     ;
    XSelectInput(param.dsp, param.win, eventmask);
    XSetWMProtocols(param.dsp, param.win, &wmDelete, true);
}

void x11::exec()
{
    Application app(this);
    app.init();
    XMapWindow(param.dsp, param.win);

    bool latch = true;

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
                    app.refreshAll();

                    /* Unless this is the last contiguous expose, don't draw the window */
                    if (event.xexpose.count == 0)
                        std::cout << "Expose!" << std::endl;
                    break;
                case ConfigureNotify:
                    /* Window has been resized; change width and height
                     * to send to place_text and place_graphics in
                     * next Expose */
                    std::cout << "Window moved or resized!" << std::endl;
                    break;

                case MotionNotify:
                {
                    if (isBtnPressed)
                    {
                        int pointx = event.xmotion.x;
                        int pointy = event.xmotion.y;
                        std::cout << "  Touch move    : [" << pointx << ',' << pointy << ']' << std::endl;

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
                    std::cout << "Touch start     : [" << pointx << ',' << pointy << ']' << std::endl;

                    msg.touchEvent = EventType::TouchStart;
                    msg.pt = Point(pointx, pointy);
                    break;
                }
                case ButtonRelease:
                {
                    isBtnPressed = false;

                    int pointx = event.xbutton.x;
                    int pointy = event.xbutton.y;
                    std::cout << "Touch end       : [" << pointx << ',' << pointy << ']' << std::endl <<
                              std::endl;

                    msg.touchEvent = EventType::TouchEnd;
                    msg.pt = Point(pointx, pointy);
                    break;
                }
                case KeyPress:
                    std::cout << "KeyPress: " << event.type << std::endl;
                    break;
                case ClientMessage:
                    // TODO Should check here for other client message types -
                    // however as the only protocol registered above is WM_DELETE_WINDOW
                    // it is safe for this small example.
                    std::cout << "WM_DELETE_WINDOW!" << std::endl;
                    param.exit = true;
                    break;
                case DestroyNotify:
                    std::cout << "Window killed!" << std::endl;
                    break;
                default:
                    std::cerr << "Unexpected event: " << event.type << std::endl;
            }
        }

        if (latch)
        {
            usleep(50000);
            latch = false;
        }

        app.setMessage(msg);
        app.quantum();

        clearMessage();
    }

}

