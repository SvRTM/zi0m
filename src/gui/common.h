/*
 * common.h
 *
 *  Created on: 25 янв. 2016 г.
 *      Author: Artem.Smirnov
 */

#ifndef GUI_COMMON_H_
#define GUI_COMMON_H_

#include <stdint.h>
#include <stddef.h>

namespace zi0m
{

struct Size final
{
    uint16_t width;
    uint16_t height;

    Size(uint16_t w = 0, uint16_t h = 0) : width(w), height(h) {}
};

struct Point final
{
    int16_t x;
    int16_t y;

    Point(int16_t x = 0, int16_t y = 0) : x(x), y(y) {}
    Point operator+(const Point &pt) const
    {
        return {int16_t(x + pt.x), int16_t(y + pt.y)};
    }
};

struct Rect final
{
    int16_t x;
    int16_t y;
    uint16_t width;
    uint16_t height;

    Rect(const Point &pt, const Size &size) : x(pt.x), y(pt.y), width(size.width),
        height(size.height) {}
    Rect(int16_t x = 0, int16_t y = 0, uint16_t width = 0, uint16_t height = 0)
        : x(x), y(y), width(width), height(height) {}

    bool contains(int16_t x, int16_t y) const
    {
        return (this->x <= x && this->x + width >= x) && (this->y <= y && this->y + height >= y);
    }

    Rect operator+(const Rect &rect) const
    {
        return {int16_t(x + rect.x), int16_t(y + rect.y), rect.width, rect.height};
    }
};

enum class EventType
{
    _None,

    TouchStart,
    TouchMove,
    TouchEnd,

    TouchEnter,
    TouchLeave
};

struct _MSG final
{
    EventType touchEvent;
    Point pt;
};

union u_color final
{
    uint32_t value;

    struct s_color final
    {
        uint8_t B;
        uint8_t G;
        uint8_t R;
        uint8_t A;
    } argb;
};
//union u_color_16
//{
//        uint16_t i_color;

//        struct s_color
//        {
//                uint8_t B:5;
//                uint8_t G:6;
//                uint8_t R:5;
//        } uc_color;
//        //uint8_t A;
//};

enum Alignment
{
    Left = 1, Right = 2, HCenter = 4,
    Top = 16, Bottom = 32, VCenter = 64,

    Center = HCenter | VCenter
};

//////////
//////////
#define LCD_COLOR_WHITE 0
#define LCD_COLOR_TEAL 1
#define LCD_COLOR_PURPLE 2
#define LCD_COLOR_BLUE 3
#define LCD_COLOR_GREYL 4
#define LCD_COLOR_GREYD 5
#define LCD_COLOR_TEALD 6
#define LCD_COLOR_PURPLED 7
#define LCD_COLOR_BLUED 8
#define LCD_COLOR_YELLOW 9
#define LCD_COLOR_GREEN 10
#define LCD_COLOR_YELLOWD 11
#define LCD_COLOR_GREEND 12
#define LCD_COLOR_RED 13
#define LCD_COLOR_REDD 14
#define LCD_COLOR_BLACK 15

#define COLOR_24B_WHITE 0xFFFFFFFFU
#define COLOR_24B_TEAL 0xFF00FFFFU
#define COLOR_24B_PURPLE 0xFFFF00FFU
#define COLOR_24B_BLUE 0xFF0000FFU
#define COLOR_24B_GREYL 0xFFC0C0C0U
#define COLOR_24B_GREYD 0xFF808080U
#define COLOR_24B_TEALD 0xFF008080U
#define COLOR_24B_PURPLED 0xFF800080U
#define COLOR_24B_BLUED 0xFF000080U
#define COLOR_24B_YELLOW 0xFFFFFF00U
#define COLOR_24B_GREEN 0xFF00FF00U
#define COLOR_24B_YELLOWD 0xFF808000U
#define COLOR_24B_GREEND 0xFF008000U
#define COLOR_24B_RED 0xFFFF0000U
#define COLOR_24B_REDD 0xFF800000U
#define COLOR_24B_BLACK 0xFF000000U

/* some RGB color definitions                                                 */
#define COLOR_16B_BLACK 0x0000       /*   0,   0,   0 */
#define COLOR_16B_NAVY 0x000F        /*   0,   0, 128 */
#define COLOR_16B_DARKGREEN 0x03E0   /*   0, 128,   0 */
#define COLOR_16B_DARKCYAN 0x03EF    /*   0, 128, 128 */
#define COLOR_16B_MAROON 0x7800      /* 128,   0,   0 */
#define COLOR_16B_PURPLE 0x780F      /* 128,   0, 128 */
#define COLOR_16B_OLIVE 0x7BE0       /* 128, 128,   0 */
#define COLOR_16B_LIGHTGREY 0xC618   /* 192, 192, 192 */
#define COLOR_16B_DARKGREY 0x7BEF    /* 128, 128, 128 */
#define COLOR_16B_BLUE 0x001F        /*   0,   0, 255 */
#define COLOR_16B_GREEN 0x07E0       /*   0, 255,   0 */
#define COLOR_16B_CYAN 0x07FF        /*   0, 255, 255 */
#define COLOR_16B_RED 0xF800         /* 255,   0,   0 */
#define COLOR_16B_MAGENTA 0xF81F     /* 255,   0, 255 */
#define COLOR_16B_YELLOW 0xFFE0      /* 255, 255,   0 */
#define COLOR_16B_WHITE 0xFFFF       /* 255, 255, 255 */
#define COLOR_16B_ORANGE 0xFD20      /* 255, 165,   0 */
#define COLOR_16B_GREENYELLOW 0xAFE5 /* 173, 255,  47 */

}
#endif /* GUI_COMMON_H_ */
