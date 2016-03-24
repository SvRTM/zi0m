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

struct Size
{
    uint16_t width;
    uint16_t height;

    Size () : width (0), height (0)
    {
    }
    Size (uint16_t w, uint16_t h) : width (w), height (h)
    {
    }
};

struct Point
{
    int16_t x;
    int16_t y;

    Point () : x (0), y (0)
    {
    }
    Point (int16_t _x, int16_t _y) : x (_x), y (_y)
    {
    }
};

struct Rect
{
    int16_t x;
    int16_t y;
    uint16_t width;
    uint16_t height;

    Rect () : x (0), y (0), width (0), height (0)
    {
    }
    Rect (int16_t _x, int16_t _y, uint16_t _width, uint16_t _height)
        : x (_x), y (_y), width (_width), height (_height)
    {
    }

    void getCoords (int16_t *x1, int16_t *y1, int16_t *x2, int16_t *y2) const
    {
        *x1 = x;
        *y1 = y;

        *x2 = x + width;
        *y2 = y + height;
    }

    bool contains (int16_t _x, int16_t _y) const
    {
        return (x <= _x && x + width >= _x) && (y <= _y && y + height >= _y);
    }

    Rect operator+(Rect &rect)
    {
        return Rect (x + rect.x, y + rect.y, rect.width, rect.height);
    }
    Rect operator+(Point pt)
    {
        return Rect (x + pt.x, y + pt.y, width, height);
    }
};

enum class EventType
{
    _None,
    TouchButtonPress,
    TouchButtonRelease
};

enum class Message
{
    _None,
    TouchUp,
    TouchDown
};
struct _MSG
{
    Message message;
    Point pt;
};

union u_color
{
    uint32_t i_color;

    struct s_color
    {
        uint8_t B;
        uint8_t G;
        uint8_t R;
        uint8_t A;
    } uc_color;
};

enum Alignment
{
    Left = 1, Right = 2, HCenter = 4,
    Top = 16, Bottom = 32, VCenter = 64,

    Center = HCenter | VCenter,
    Shift = 128
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

#endif /* GUI_COMMON_H_ */
