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

        Size()
                : width(0), height(0)
        {
        }
        Size(uint16_t w, uint16_t h)
                : width(w), height(h)
        {
        }
};

struct Point
{
        int16_t x;
        int16_t y;

        Point()
                : x(0), y(0)
        {
        }
        Point(int16_t _x, int16_t _y)
                : x(_x), y(_y)
        {
        }
};

struct Rect
{
        int16_t x;
        int16_t y;
        uint16_t width;
        uint16_t height;

        Rect()
                : x(0), y(0), width(0), height(0)
        {
        }
        Rect(int16_t _x, int16_t _y, uint16_t _width, uint16_t _height)
                : x(_x), y(_y), width(_width), height(_height)
        {
        }

        void getCoords(int16_t *x1, int16_t *y1, int16_t *x2, int16_t *y2) const
        {
            *x1 = x;
            *y1 = y;

            *x2 = x + width;
            *y2 = y + height;
        }

        bool contains(int16_t _x, int16_t _y) const
        {
            return (x <= _x && x + width >= _x) && (y <= _y && y + height >= _y);
        }

        Rect operator+(Rect &rect)
        {
            return Rect(x + rect.x, y + rect.y, rect.width, rect.height);
        }
};

enum class EventType
{
    None, TouchButtonPress, TouchButtonRelease
};

enum class Message
{
    None, TouchUp, TouchDown
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

//////////
//////////
#define LCD_COLOR_WHITE         0
#define LCD_COLOR_TEAL          1
#define LCD_COLOR_PURPLE        2
#define LCD_COLOR_BLUE          3
#define LCD_COLOR_GREYL         4
#define LCD_COLOR_GREYD         5
#define LCD_COLOR_TEALD         6
#define LCD_COLOR_PURPLED       7
#define LCD_COLOR_BLUED         8
#define LCD_COLOR_YELLOW        9
#define LCD_COLOR_GREEN         10
#define LCD_COLOR_YELLOWD       11
#define LCD_COLOR_GREEND        12
#define LCD_COLOR_RED           13
#define LCD_COLOR_REDD          14
#define LCD_COLOR_BLACK         15

#define COLOR_24B_WHITE         0x00FFFFFFU
#define COLOR_24B_TEAL          0x0000FFFFU
#define COLOR_24B_PURPLE        0x00FF00FFU
#define COLOR_24B_BLUE          0x000000FFU
#define COLOR_24B_GREYL         0x00C0C0C0U
#define COLOR_24B_GREYD         0x00808080U
#define COLOR_24B_TEALD         0x00008080U
#define COLOR_24B_PURPLED       0x00800080U
#define COLOR_24B_BLUED         0x00000080U
#define COLOR_24B_YELLOW        0x00FFFF00U
#define COLOR_24B_GREEN         0x0000FF00U
#define COLOR_24B_YELLOWD       0x00808000U
#define COLOR_24B_GREEND        0x00008000U
#define COLOR_24B_RED           0x00FF0000U
#define COLOR_24B_REDD          0x00800000U
#define COLOR_24B_BLACK         0x00000000U

#endif /* GUI_COMMON_H_ */
