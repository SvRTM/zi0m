/*
 * EmuLcd.cpp
 *
 *  Created on: 31 янв. 2016 г.
 *      Author: Artem.Smirnov
 */

#include "EmuLcd.h"
#include <iostream>
#include <windows.h>
#undef min
#undef max

int offset_x = 0;
int offset_y = 0;

EmuLcd::EmuLcd(HWND hWnd)
{
    this->hWnd = hWnd;
}

EmuLcd::~EmuLcd()
{    // TODO Auto-generated destructor stub
}

void EmuLcd::setPoint(int x, int y, const u_color &color)
{
    HDC hdc = GetDC(hWnd);
    SetPixel(hdc, x + offset_x, y + offset_y,
            RGB(color.uc_color.R, color.uc_color.G, color.uc_color.B));
    ReleaseDC(hWnd, hdc);
}

void EmuLcd::fillRect(const Rect &rect, const u_color &color)
{
    HDC hdc = GetDC(hWnd);
    //std::cout << std::hex << color.i_color << "  A:" << std::hex
    //        << (int) color.uc_color.A << "  R:" << std::hex
    //        << (int) color.uc_color.R << "  G:" << std::hex
    //        << (int) color.uc_color.G << "  B:" << std::hex
    //        << (int) color.uc_color.B << std::endl;
    HBRUSH brush = CreateSolidBrush(
            RGB(color.uc_color.R, color.uc_color.G, color.uc_color.B));
    SelectObject(hdc, brush);
    std::cout << "x:" << rect.x << " y:" << rect.y << "  w:" << rect.width
            << " h:" << rect.height << std::endl;
    RECT r;
    r.left = rect.x + offset_x;
    r.top = rect.y + offset_y;
    r.right = (rect.x + rect.width) /*+ 1*/+ offset_x;
    r.bottom = (rect.y + rect.height)/* + 1*/+ offset_y;
    FillRect(hdc, &r, brush);
    DeleteObject(brush);
    ReleaseDC(hWnd, hdc);
}

uint16_t EmuLcd::getWidth()
{
    return 320;
}
uint16_t EmuLcd::getHight()
{
    return 240;
}

/*
 public static Color RemoveAlpha(Color foreground, Color background)
 {
 if (foreground.A == 255)
 return foreground;

 var alpha = foreground.A / 255.0;
 var diff = 1.0 - alpha;
 return Color.FromArgb(255,
 (byte)(foreground.R * alpha + background.R * diff),
 (byte)(foreground.G * alpha + background.G * diff),
 (byte)(foreground.B * alpha + background.B * diff));
 }

 */
