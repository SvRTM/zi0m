/*
 * x11.cpp
 *
 *  Created on: 11 марта 2016 г.
 *      Author: Artem.Smirnov
 */

//#ifdef _linux1_
#include "x11.h"
#include <stdio.h>

x11::x11()
{
    eventmask = ButtonPressMask | ButtonReleaseMask | ExposureMask
            | KeyPressMask;
    //| StructureNotifyMask | PropertyChangeMask | VisibilityChangeMask
    //| FocusChangeMask;

    if (!(display = XOpenDisplay(NULL)))
    {
        perror("XOpenDisplay");
        //exit(1);
    }

    int screen = DefaultScreen(display);
    colormap = DefaultColormap(display, screen);

    Window root = RootWindow(display, screen);
    long fgcolor = BlackPixel(display, screen);
    long bgcolor = WhitePixel(display, screen);

    //window = XCreateSimpleWindow(display, root, 0, 0, 320, 240, 2, fgcolor,
    //        bgcolor);
    XSetWindowAttributes attributes { };
    attributes.background_pixel = XWhitePixel(display, screen);
    window = XCreateWindow(display, root, 0, 0, 320, 240, 2,
            DefaultDepth(display, screen), InputOutput,
            DefaultVisual(display, screen), CWBackPixel | CWBorderPixel,
            &attributes);

    XMapWindow(display, window);
    XSelectInput(display, window, eventmask);
    /* flush all pending requests to the X server. */
    XFlush(display);

    XColor color, ignore;
    Colormap cmap = DefaultColormap(display, screen);
    XAllocNamedColor(display, cmap, "Navy", &color, &ignore);
    fgcolor = color.pixel;

    XGCValues gcval;
    gcval.foreground = fgcolor;
    gcval.background = bgcolor;
    gcval.line_width = 5;
    gc = XCreateGC(display, window, GCForeground | GCBackground | GCLineWidth,
            &gcval);
    //gc = XCreateGC(dpy, window, NULL, NULL);

    /*
     if (mono_src) {
     if (!d->crgn.isEmpty()) {
     Pixmap comb = XCreatePixmap(d->dpy, d->hd, sw, sh, 1);
     GC cgc = XCreateGC(d->dpy, comb, 0, 0);
     XSetForeground(d->dpy, cgc, 0);
     XFillRectangle(d->dpy, comb, cgc, 0, 0, sw, sh);
     int num;
     XRectangle *rects = (XRectangle *)qt_getClipRects(d->crgn, num);
     XSetClipRectangles(d->dpy, cgc, -x, -y, rects, num, Unsorted);
     XCopyArea(d->dpy, pixmap.handle(), comb, cgc, sx, sy, sw, sh, 0, 0);
     XFreeGC(d->dpy, cgc);

     XSetClipMask(d->dpy, d->gc, comb);
     XSetClipOrigin(d->dpy, d->gc, x, y);
     XFreePixmap(d->dpy, comb);
     } else {
     XSetClipMask(d->dpy, d->gc, pixmap.handle());
     XSetClipOrigin(d->dpy, d->gc, x - sx, y - sy);
     }

     if (mono_dst) {
     XSetForeground(d->dpy, d->gc, qGray(d->cpen.color().rgb()) > 127 ? 0 : 1);
     } else {
     QColormap cmap = QColormap::instance(d->scrn);
     XSetForeground(d->dpy, d->gc, cmap.pixel(d->cpen.color()));
     }
     XFillRectangle(d->dpy, d->hd, d->gc, x, y, sw, sh);
     restore_clip = true;
     } else if (mono_dst && !mono_src) {
     QBitmap bitmap(pixmap);
     XCopyArea(d->dpy, bitmap.handle(), d->hd, d->gc, sx, sy, sw, sh, x, y);
     } else {
     XCopyArea(d->dpy, pixmap.handle(), d->hd, d->gc, sx, sy, sw, sh, x, y);
     }*/
}

x11::~x11()
{
    //XUnloadFont(dpy, font_info->fid);
    XFreeGC(display, gc);
    XUnmapWindow(display, window);
    XDestroyWindow(display, window);
    XCloseDisplay(display);

    /*
     XColor xcolour;

     // I guess XParseColor will work here
     xcolour.red = 32000; xcolour.green = 65000; xcolour.blue = 32000;
     xcolour.flags = DoRed | DoGreen | DoBlue;
     XAllocColor(d, cmap, &xcolour);

     XSetForeground(d, gc, xcolour.pixel);
     XFillRectangle(d, w, gc, 0, 0, winatt.width, 30);
     XFlush(d);




     if(IsNull(width) || IsNull(color)) return;
     SetLineStyle(width);
     {
     if(width == linewidth) return;
     linewidth = width;
     if(IsNull(width))
     width = 1;
     if(width < PEN_SOLID) {
     static const char dash[] = { 18, 6 };
     static const char dot[] = { 3, 3 };
     static const char dashdot[] = { 9, 6, 3, 6 };
     static const char dashdotdot[] = { 9, 3, 3, 3, 3, 3 };
     static struct {
     const char *dash;
     int   len;
     } ds[] = {
     { dash, __countof(dash) },
     { dot, __countof(dot) },
     { dashdot, __countof(dashdot) },
     { dashdotdot, __countof(dashdotdot) }
     };
     int i = -(width - PEN_DASH);
     ASSERT(i >= 0 && i < 4);
     XSetDashes(Xdisplay, gc, 0, ds[i].dash, ds[i].len);
     }
     XSetLineAttributes(Xdisplay, gc, max(width, 1),
     width < PEN_SOLID ? LineOnOffDash : LineSolid, CapRound, JoinRound);
     }
     SetForeground(color);
     {
     LTIMING("SetForeground");
     int p = GetXPixel(color.GetR(), color.GetG(), color.GetB());
     {
     dword GetTrueColorPixel(int r, int g, int b)
     {
     return Xred.Do(r) | Xgreen.Do(g) | Xblue.Do(b);
     }

     }
     if(p == foreground) return;
     LTIMING("XSetForeground");
     LLOG("XSetForeground " << color);
     foreground = p;
     XSetForeground(Xdisplay, gc, foreground);
     }
     XDrawLine(Xdisplay, dw, gc,
     x1 + actual_offset.x, y1 + actual_offset.y,
     x2 + actual_offset.x, y2 + actual_offset.y);




     */
}

void x11::run()
{
    XEvent event;

    bool FirstPt = true;
    int pointx, pointy;

    Atom wmDelete = XInternAtom(display, "WM_DELETE_WINDOW", false);
    XSetWMProtocols(display, window, &wmDelete, true);

    bool loop = true;
    while (loop)
    {
        //XWindowEvent(dpy, window, eventmask, &event);
        XNextEvent(display, &event);
        switch (event.type)
        {
            case Expose:
                /* Unless this is the last contiguous expose,
                 * don't draw the window */

                XClearWindow(display, window);
                break;
            case ConfigureNotify:
                /* Window has been resized; change width and height
                 * to send to place_text and place_graphics in
                 * next Expose */
                printf("Window moved or resized!\n");
                break;
            case ButtonPress:
                if (FirstPt)
                {
                    FirstPt = false;
                    pointx = event.xbutton.x;
                    pointy = event.xbutton.y;
                    //XSetForeground();
                    XDrawPoint(display, window, gc, pointx, pointy);
                    break;

                } else
                {
                    FirstPt = true;
                    XDrawLine(display, window, gc, pointx, pointy,
                            event.xbutton.x, event.xbutton.y);
                    break;
                }
            case ButtonRelease:
                printf("Button released : %d\n", event.xbutton.button - 1);
                break;
            case KeyPress:
                fprintf(stdout, "KeyPress: %d\n", event.type);
                //exit(0);

                break;
            case ClientMessage:
                // TODO Should check here for other client message types -
                // however as the only protocol registered above is WM_DELETE_WINDOW
                // it is safe for this small example.
                loop = false;
                break;
            case DestroyNotify:
                printf("Window killed!\n");
                break;
            default:
                fprintf(stderr, "Unexpected event: %d\n", event.type);
        }
    }
}
//#endif
