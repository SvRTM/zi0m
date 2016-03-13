/*
 * EmuLcd.cpp
 *
 *  Created on: 31 янв. 2016 г.
 *      Author: Artem.Smirnov
 */

#include "EmuLcd.h"
#include <iostream>

#ifdef WIN32
#include <windows.h>
#undef min
#undef max
#elif LINUX
#endif

int offset_x = 0;
int offset_y = 0;

#ifdef WIN32
EmuLcd::EmuLcd(HWND hWnd)
{
    this->hWnd = hWnd;
}
#elif LINUX
EmuLcd::EmuLcd(Display *display, Drawable window, GC gc, Colormap cmap)
{
    this->display = display;
    this->window = window;
    this->gc = gc;
    this->cmap = cmap;
}
#endif
EmuLcd::~EmuLcd()
{
}

void EmuLcd::setPoint(int x, int y, const u_color &color)
{
#ifdef WIN32
    HDC hdc = GetDC(hWnd);
    SetPixel(hdc, x + offset_x, y + offset_y,
            RGB(color.uc_color.R, color.uc_color.G, color.uc_color.B));
    ReleaseDC(hWnd, hdc);
#elif LINUX
    XColor xcolour
    {};

    uint16_t r = color.uc_color.R;
    xcolour.red = r << 8;
    uint16_t g = color.uc_color.G;
    xcolour.green = g << 8;
    uint16_t b = color.uc_color.B;
    xcolour.blue = b << 8;

    xcolour.flags = DoRed | DoGreen | DoBlue;
    XAllocColor(display, cmap, &xcolour);
    XSetForeground(display, gc, xcolour.pixel);
    XDrawPoint(display, window, gc, x + offset_x, y + offset_y);
    XFlush(display);
#endif
}

void EmuLcd::fillRect(const Rect &rect, const u_color &color)
{
#ifdef WIN32
    HDC hdc = GetDC(hWnd);
    HBRUSH brush = CreateSolidBrush(
            RGB(color.uc_color.R, color.uc_color.G, color.uc_color.B));
    SelectObject(hdc, brush);

    RECT r;
    r.left = rect.x + offset_x;
    r.top = rect.y + offset_y;
    r.right = (rect.x + rect.width) /*+ 1*/+ offset_x;
    r.bottom = (rect.y + rect.height)/* + 1*/+ offset_y;
    FillRect(hdc, &r, brush);
    DeleteObject(brush);
    ReleaseDC(hWnd, hdc);
#elif LINUX
    XColor xcolour
    {};

    uint16_t r = color.uc_color.R;
    xcolour.red = r << 8;
    uint16_t g = color.uc_color.G;
    xcolour.green = g << 8;
    uint16_t b = color.uc_color.B;
    xcolour.blue = b << 8;

    xcolour.flags = DoRed | DoGreen | DoBlue;
    XAllocColor(display, cmap, &xcolour);
    XSetForeground(display, gc, xcolour.pixel); //xcolour.pixel

    XFillRectangle(display,window,gc,rect.x + offset_x,rect.y + offset_y,(rect.x + rect.width) /*+ 1*/+ offset_x,(rect.y + rect.height)/* + 1*/+ offset_y);
    XFlush(display);
#endif
}

uint16_t EmuLcd::getWidth()
{
    return 320;
}
uint16_t EmuLcd::getHight()
{
    return 240;
}

