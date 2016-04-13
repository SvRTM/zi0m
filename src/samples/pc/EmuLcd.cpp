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

void EmuLcd::setColor(const u_color &color)
{
    XColor xcolour;

#ifdef RGB888
    uint16_t r = color.argb.R;
    xcolour.red = r << 8;
    uint16_t g = color.argb.G;
    xcolour.green = g << 8;
    uint16_t b = color.argb.B;
    xcolour.blue = b << 8;
#elif RGB565
    uint16_t r = color.rgb565.R;
    xcolour.red = r << 11;
    uint16_t g = color.rgb565.G;
    xcolour.green = g << 10;
    uint16_t b = color.rgb565.B;
    xcolour.blue = b << 11;
#endif

    xcolour.flags = DoRed | DoGreen | DoBlue;
    XAllocColor(x11data->dsp, x11data->cmap, &xcolour);
    XSetForeground(x11data->dsp, x11data->ctx, xcolour.pixel);
}

void EmuLcd::drawPoint(int16_t x, int16_t y, const u_color &color)
{
#ifdef PLATFORM_WIN32
    HDC hdc = GetDC(hWnd);
    SetPixel(hdc, x, y,
             RGB(color.uc_color.R, color.uc_color.G, color.uc_color.B));
    ReleaseDC(hWnd, hdc);

#elif PLATFORM_LINUX
    setColor(color);
    usleep(10);

    XDrawPoint(x11data->dsp, x11data->win, x11data->ctx, x, y);
    usleep(50);
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
    setColor(color);
    usleep(10);

    XFillRectangle(x11data->dsp, x11data->win, x11data->ctx, rect.x, rect.y,
                   rect.width, rect.height);
    usleep(10);
    //    int _x = rect.x, _y = rect.y;
    //    int _w = rect.width, _h = rect.height;
    //    for (int y = _y; y < _y + _h; ++y)
    //        for (int x = _x; x < _x + _w; ++x)
    //            XDrawPoint(param->d_, param->win, param->ctx, x, y);
#endif
}

/**
 * @author Zingl Alois
 * @date 17.12.2012
 * @version 1.1
 * @see http://members.chello.at/~easyfilter/bresenham.html
 */
void EmuLcd::circle(int16_t cx, int16_t cy, uint16_t radius, const u_color &color)
{
    setColor(color);

    int16_t x = -radius, y = 0, err = 2 - 2 * radius;   /* bottom left to top right */
    do
    {
        /*   I. Quadrant +x +y */
        XDrawPoint(x11data->dsp, x11data->win, x11data->ctx, cx - x, cy + y);
        /*  II. Quadrant -x +y */
        XDrawPoint(x11data->dsp, x11data->win, x11data->ctx, cx - y, cy - x);
        /* III. Quadrant -x -y */
        XDrawPoint(x11data->dsp, x11data->win, x11data->ctx, cx + x, cy - y);
        /*  IV. Quadrant +x -y */
        XDrawPoint(x11data->dsp, x11data->win, x11data->ctx, cx + y, cy + x);

        int16_t r = err;
        if (r <= y)
            err += ++y * 2 + 1;                         /* e_xy+e_y < 0 */
        if (r > x || err > y)                               /* e_xy+e_x > 0 or no 2nd y-step */
            err += ++x * 2 + 1;                         /* -> x-step now */
    }
    while (x < 0);
}

void EmuLcd::circle(int16_t cx, int16_t cy, uint16_t radius, int16_t dy,
                    const u_color &color1, const u_color &color2)
{
    int16_t x = -radius, y = 0, err = 2 - 2 * radius;   /* bottom left to top right */
    do
    {
        if (cy + y <= 2 * cy - dy)
            setColor(color2);
        else
            setColor(color1);
        /*   I. Quadrant +x +y */
        XDrawPoint(x11data->dsp, x11data->win, x11data->ctx, cx - x, cy + y);

        if (cy + x <= 2 * cy - dy)
            setColor(color2);
        else
            setColor(color1);
        /*  IV. Quadrant +x -y */
        XDrawPoint(x11data->dsp, x11data->win, x11data->ctx, cx + y, cy + x);


        if ( cy - x <= dy)
            setColor(color2);
        else
            setColor(color1);
        /*  II. Quadrant -x +y */
        XDrawPoint(x11data->dsp, x11data->win, x11data->ctx, cx - y, cy - x);

        if ( cy - y <= dy)
            setColor(color2);
        else
            setColor(color1);
        /* III. Quadrant -x -y */
        XDrawPoint(x11data->dsp, x11data->win, x11data->ctx, cx + x, cy - y);

        int16_t r = err;
        if (r <= y)
            err += ++y * 2 + 1;                         /* e_xy+e_y < 0 */
        if (r > x || err > y)                               /* e_xy+e_x > 0 or no 2nd y-step */
            err += ++x * 2 + 1;                         /* -> x-step now */
    }
    while (x < 0);
}

/**
 * @author Zingl Alois
 * @date 17.12.2012
 * @version 1.1
 * @see http://members.chello.at/~easyfilter/bresenham.html
 */
void EmuLcd::fillCircle(int16_t cx, int16_t cy, uint16_t radius, const u_color &color)
{
    setColor(color);

    int16_t x = -radius, y = 0, err = 2 - 2 * radius;   /* bottom left to top right */
    drawLine(cx + x, cy + y, cx - x, cy + y);
    do
    {
        int16_t r = err;
        if (r <= y)
            err += ++y * 2 + 1;                         /* e_xy+e_y < 0 */
        if (r > x || err > y)                               /* e_xy+e_x > 0 or no 2nd y-step */
            err += ++x * 2 + 1;                         /* -> x-step now */

        if (r < y)
        {
            drawLine(cx + x, cy + y, cx - x, cy + y);
            drawLine(cx + x, cy - y, cx - x, cy - y);
        }
    }
    while (x < 0);
}

void EmuLcd::drawLine(int16_t x1, int16_t y1, int16_t x2, int16_t y2,
                      const u_color &color)
{
    setColor(color);
    drawLine(x1, y1, x2, y2);
}

/**
 * @author Zingl Alois
 * @date 17.12.2012
 * @version 1.1
 * @see http://members.chello.at/~easyfilter/bresenham.html
 */
void EmuLcd::drawLine(int16_t x1, int16_t y1, int16_t x2, int16_t y2)
{
    int16_t dx = abs(x2 - x1), sx = x1 < x2 ? 1 : -1;
    int16_t dy = -abs(y2 - y1), sy = y1 < y2 ? 1 : -1;
    int16_t err = dx + dy, e2;                        /* error value e_xy */

    for (;;) /* loop */
    {
        XDrawPoint(x11data->dsp, x11data->win, x11data->ctx, x1, y1);
        e2 = 2 * err;
        if (e2 >= dy)                                       /* e_xy+e_x > 0 */
        {
            if (x1 == x2)
                break;
            err += dy;
            x1 += sx;
        }
        if (e2 <= dx)                                       /* e_xy+e_y < 0 */
        {
            if (y1 == y2)
                break;
            err += dx;
            y1 += sy;
        }
    }
}
