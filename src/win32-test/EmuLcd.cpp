/*
 * EmuLcd.cpp
 *
 *  Created on: 31 янв. 2016 г.
 *      Author: Artem.Smirnov
 */

#include "EmuLcd.h"

#ifdef PLATFORM_WIN32
EmuLcd::EmuLcd(HWND hWnd)
{
    this->hWnd = hWnd;
}
#elif PLATFORM_LINUX
EmuLcd::EmuLcd(const RenderData *x11data)
{
    this->x11data = x11data;
}
#endif
EmuLcd::~EmuLcd()
{
}

void EmuLcd::setPoint(int16_t x, int16_t y, const u_color &color)
{
#ifdef PLATFORM_WIN32
    HDC hdc = GetDC(hWnd);
    SetPixel(hdc, x, y, RGB(color.uc_color.R, color.uc_color.G, color.uc_color.B));
    ReleaseDC(hWnd, hdc);

#elif PLATFORM_LINUX
    XColor xcolour;
    uint16_t r = color.uc_color.R;
    xcolour.red = r << 8;
    uint16_t g = color.uc_color.G;
    xcolour.green = g << 8;
    uint16_t b = color.uc_color.B;
    xcolour.blue = b << 8;

    xcolour.flags = DoRed | DoGreen | DoBlue;
    XAllocColor(x11data->d_, x11data->cmap, &xcolour);
    XSetForeground(x11data->d_, x11data->ctx, xcolour.pixel);
    XDrawPoint(x11data->d_, x11data->win, x11data->ctx, x, y);
#endif
}

void EmuLcd::fillRect(const Rect &rect, const u_color &color)
{
#ifdef PLATFORM_WIN32
    HDC hdc = GetDC(hWnd);
    HBRUSH brush = CreateSolidBrush(
                       RGB(color.uc_color.R, color.uc_color.G, color.uc_color.B));
    SelectObject(hdc, brush);

    RECT r;
    r.left = rect.x;
    r.top = rect.y;
    r.right = rect.x + rect.width;
    r.bottom = rect.y + rect.height;
    FillRect(hdc, &r, brush);
    DeleteObject(brush);
    ReleaseDC(hWnd, hdc);

#elif PLATFORM_LINUX
    XColor xcolour;
    uint16_t r = color.uc_color.R;
    xcolour.red = r << 8;
    uint16_t g = color.uc_color.G;
    xcolour.green = g << 8;
    uint16_t b = color.uc_color.B;
    xcolour.blue = b << 8;

    xcolour.flags = DoRed | DoGreen | DoBlue;
    XAllocColor(x11data->d_, x11data->cmap, &xcolour);
    XSetForeground(x11data->d_, x11data->ctx, xcolour.pixel);

    XFillRectangle(x11data->d_, x11data->win, x11data->ctx, rect.x, rect.y,
                   rect.width, rect.height);

    //    int _x = rect.x, _y = rect.y;
    //    int _w = rect.width, _h = rect.height;
    //    for (int y = _y; y < _y + _h; ++y)
    //        for (int x = _x; x < _x + _w; ++x)
    //            XDrawPoint(param->d_, param->win, param->ctx, x, y);
#endif
}

const uint16_t EmuLcd::getWidth() const
{
    return 320;
}
const uint16_t EmuLcd::getHight() const
{
    return 240;
}
