/*
 * Copyright © 2016 Artem Smirnov
 * All right reserved.
 * Author: Artem Smirnov <msvrtm@gmail.com>
 * License: http://www.gnu.org/licenses/gpl.txt
 */

#include "EmuLcd.h"
#include <unistd.h>

//#define usleep usleep
#define usleep(n)

#ifdef PLATFORM_WIN32
#ifdef RGB565
/** Used information from the website: www.tune-it.ru/web/il/home/-/blogs/36120 */
const uint8_t EmuLcd::table5[32] = {0, 8, 16, 25, 33, 41, 49, 58, 66, 74, 82,
                                    90, 99, 107, 115, 123, 132, 140, 148, 156,
                                    165, 173, 181, 189, 197, 206, 214, 222, 230,
                                    239, 247, 255
                                   };
const uint8_t EmuLcd::table6[64] = {0, 4, 8, 12, 16, 20, 24, 28, 32, 36, 40, 45,
                                    49, 53, 57, 61, 65, 69, 73, 77, 81, 85, 89,
                                    93, 97, 101, 105, 109, 113, 117, 121, 125,
                                    130, 134, 138, 142, 146, 150, 154, 158, 162,
                                    166, 170, 174, 178, 182, 186, 190, 194, 198,
                                    202, 206, 210, 215, 219, 223, 227, 231, 235,
                                    239, 243, 247, 251, 255
                                   };
#endif
EmuLcd::EmuLcd(HWND hWnd) : hWnd(hWnd)
{
}
#elif PLATFORM_LINUX
EmuLcd::EmuLcd(const RenderData *x11data)
{
    this->x11data = x11data;
}
#endif

#ifdef PLATFORM_WIN32
COLORREF EmuLcd::toColorRef(const u_color color)
{
#ifdef RGB888
    return RGB(color.argb.R, color.argb.G, color.argb.B);
#elif RGB565
    /** Used information from the website: www.tune-it.ru/web/il/home/-/blogs/36120 */
    return RGB(table5[color.rgb565.R], table6[color.rgb565.G], table5[color.rgb565.B]);
#endif
}

#elif PLATFORM_LINUX
void EmuLcd::setColor(const u_color color)
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
#endif

void EmuLcd::drawPoint(int16_t x, int16_t y, const u_color color)
{
#ifdef PLATFORM_WIN32
    HDC hdc = GetDC(hWnd);
    SetPixel(hdc, x, y, toColorRef(color));
    ReleaseDC(hWnd, hdc);
    usleep(50);
#elif PLATFORM_LINUX
    setColor(color);
    usleep(10);

    XDrawPoint(x11data->dsp, x11data->win, x11data->ctx, x, y);
#endif
    usleep(50);
}

void EmuLcd::fillRect(const Rect &rect, const u_color color)
{
#ifdef PLATFORM_WIN32
    HDC hdc = GetDC(hWnd);
    HBRUSH brush = CreateSolidBrush(toColorRef(color));
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
#endif
    usleep(10);
}

/**
 * @author Zingl Alois
 * @date 17.12.2012
 * @version 1.1
 * @see http://members.chello.at/~easyfilter/bresenham.html
 */
void EmuLcd::drawCircle(int16_t cx, int16_t cy, uint16_t radius, const u_color color)
{
#ifdef PLATFORM_LINUX
    setColor(color);
#endif

    int16_t x = -radius, y = 0, err = 2 - 2 * radius;   /* bottom left to top right */
    do
    {
#ifdef PLATFORM_WIN32
        /*   I. Quadrant +x +y */
        drawPoint(cx - x, cy + y, color);
        /*  II. Quadrant -x +y */
        drawPoint(cx - y, cy - x, color);
        /* III. Quadrant -x -y */
        drawPoint(cx + x, cy - y, color);
        /*  IV. Quadrant +x -y */
        drawPoint(cx + y, cy + x, color);

#elif PLATFORM_LINUX
        /*   I. Quadrant +x +y */
        XDrawPoint(x11data->dsp, x11data->win, x11data->ctx, cx - x, cy + y);
        /*  II. Quadrant -x +y */
        XDrawPoint(x11data->dsp, x11data->win, x11data->ctx, cx - y, cy - x);
        /* III. Quadrant -x -y */
        XDrawPoint(x11data->dsp, x11data->win, x11data->ctx, cx + x, cy - y);
        /*  IV. Quadrant +x -y */
        XDrawPoint(x11data->dsp, x11data->win, x11data->ctx, cx + y, cy + x);
#endif

        int16_t r = err;
        if (r <= y)
            err += ++y * 2 + 1;     /* e_xy+e_y < 0 */
        if (r > x || err > y)       /* e_xy+e_x > 0 or no 2nd y-step */
            err += ++x * 2 + 1;     /* -> x-step now */
    }
    while (x < 0);
}

void EmuLcd::drawCircle(int16_t cx, int16_t cy, uint16_t radius, int16_t dy,
                        const u_color color1, const u_color color2)
{
    int16_t x = -radius, y = 0, err = 2 - 2 * radius;   /* bottom left to top right */
    do
    {
        if (cy + y <= 2 * cy - dy)
#ifdef PLATFORM_WIN32
            drawPoint(cx - x, cy + y, color2);
#elif PLATFORM_LINUX
            setColor(color2);
#endif
        else
#ifdef PLATFORM_WIN32
            drawPoint(cx - x, cy + y, color1);
#elif PLATFORM_LINUX
            setColor(color1);
        /*   I. Quadrant +x +y */
        XDrawPoint(x11data->dsp, x11data->win, x11data->ctx, cx - x, cy + y);
#endif

        if (cy + x <= 2 * cy - dy)
#ifdef PLATFORM_WIN32
            drawPoint(cx + y, cy + x, color2);
#elif PLATFORM_LINUX
            setColor(color2);
#endif
        else
#ifdef PLATFORM_WIN32
            drawPoint(cx + y, cy + x, color1);
#elif PLATFORM_LINUX
            setColor(color1);
        /*  IV. Quadrant +x -y */
        XDrawPoint(x11data->dsp, x11data->win, x11data->ctx, cx + y, cy + x);
#endif

        if ( cy - x <= dy)
#ifdef PLATFORM_WIN32
            drawPoint(cx - y, cy - x, color2);
#elif PLATFORM_LINUX
            setColor(color2);
#endif
        else
#ifdef PLATFORM_WIN32
            drawPoint(cx - y, cy - x, color1);
#elif PLATFORM_LINUX
            setColor(color1);
        /*  II. Quadrant -x +y */
        XDrawPoint(x11data->dsp, x11data->win, x11data->ctx, cx - y, cy - x);
#endif

        if ( cy - y <= dy)
#ifdef PLATFORM_WIN32
            drawPoint(cx + x, cy - y, color2);
#elif PLATFORM_LINUX
            setColor(color2);
#endif
        else
#ifdef PLATFORM_WIN32
            drawPoint(cx + x, cy - y, color1);
#elif PLATFORM_LINUX
            setColor(color1);
        /* III. Quadrant -x -y */
        XDrawPoint(x11data->dsp, x11data->win, x11data->ctx, cx + x, cy - y);
#endif

        int16_t r = err;
        if (r <= y)
            err += ++y * 2 + 1;     /* e_xy+e_y < 0 */
        if (r > x || err > y)       /* e_xy+e_x > 0 or no 2nd y-step */
            err += ++x * 2 + 1;     /* -> x-step now */
    }
    while (x < 0);
}

/**
 * @author Zingl Alois
 * @date 17.12.2012
 * @version 1.1
 * @see http://members.chello.at/~easyfilter/bresenham.html
 */
void EmuLcd::fillCircle(int16_t cx, int16_t cy, uint16_t radius, const u_color color)
{
#ifdef PLATFORM_LINUX
    setColor(color);
#endif

    int16_t x = -radius, y = 0, err = 2 - 2 * radius;   /* bottom left to top right */
    p_drawLine(cx + x, cy + y, cx - x, cy + y
#ifdef PLATFORM_WIN32
               , color
#endif
              );
    do
    {
        int16_t r = err;
        if (r <= y)
            err += ++y * 2 + 1;     /* e_xy+e_y < 0 */
        if (r > x || err > y)       /* e_xy+e_x > 0 or no 2nd y-step */
            err += ++x * 2 + 1;     /* -> x-step now */

        if (r < y)
        {
            p_drawLine(cx + x, cy + y, cx - x, cy + y
#ifdef PLATFORM_WIN32
                       , color
#endif
                      );
            p_drawLine(cx + x, cy - y, cx - x, cy - y
#ifdef PLATFORM_WIN32
                       , color
#endif
                      );
        }
    }
    while (x < 0);
}

void EmuLcd::drawLine(int16_t x1, int16_t y1, int16_t x2, int16_t y2, const u_color color)
{
#ifdef PLATFORM_LINUX
    setColor(color);
#endif
    p_drawLine(x1, y1, x2, y2
#ifdef PLATFORM_WIN32
               , color
#endif
              );
}
void EmuLcd::drawHLine(int16_t x, int16_t y, uint16_t width, const u_color color)
{
#ifdef PLATFORM_LINUX
    setColor(color);
#endif
    p_drawLine(x, y, x + width - 1, y
#ifdef PLATFORM_WIN32
               , color
#endif
              );
}
void EmuLcd::drawVLine(int16_t x, int16_t y, uint16_t height, const u_color color)
{
#ifdef PLATFORM_LINUX
    setColor(color);
#endif
    p_drawLine(x, y, x, y + height - 1
#ifdef PLATFORM_WIN32
               , color
#endif
              );
}

/**
 * @author Zingl Alois
 * @date 17.12.2012
 * @version 1.1
 * @see http://members.chello.at/~easyfilter/bresenham.html
 */
void EmuLcd::p_drawLine(int16_t x1, int16_t y1, int16_t x2, int16_t y2
#ifdef PLATFORM_WIN32
                        , const u_color color
#endif
                       )
{
    int16_t dx = abs(x2 - x1), sx = x1 < x2 ? 1 : -1;
    int16_t dy = -abs(y2 - y1), sy = y1 < y2 ? 1 : -1;
    int16_t err = dx + dy, e2;  /* error value e_xy */

    for (;;) /* loop */
    {
#ifdef PLATFORM_WIN32
        drawPoint(x1, y1, color);
#elif PLATFORM_LINUX
        XDrawPoint(x11data->dsp, x11data->win, x11data->ctx, x1, y1);
#endif

        e2 = 2 * err;
        if (e2 >= dy)       /* e_xy+e_x > 0 */
        {
            if (x1 == x2)
                break;
            err += dy;
            x1 += sx;
        }
        if (e2 <= dx)       /* e_xy+e_y < 0 */
        {
            if (y1 == y2)
                break;
            err += dx;
            y1 += sy;
        }
    }
}
