/*
 * common.h
 *
 *  Created on: 25 янв. 2016 г.
 *      Author: Artem.Smirnov
 */

#ifndef GUI_COMMON_H_
#define GUI_COMMON_H_

#include "config.h"

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

// TODO: enum_vale https://www.reddit.com/r/cpp/comments/14oqo9/a_nice_helper_function_for_c11s_enum_classes/
enum class EventType
{
    None,

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

#ifdef RGB888
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
#elif  RGB565
union u_color
{
    uint16_t value;

    struct s_color
    {
        uint16_t B: 5;
        uint16_t G: 6;
        uint16_t R: 5;
    } rgb565;
};
#endif

enum Alignment
{
    Left = 1, Right = 2, HCenter = 4,
    Top = 16, Bottom = 32, VCenter = 64,

    Center = HCenter | VCenter
};

//////////
#ifdef RGB888

#define COLOR_WHITE     0xFFFFFFFFU
#define COLOR_BLUE       0xFF0000FFU
#define COLOR_BLUED     0xFF000080U
#define COLOR_GREEN     0xFF00FF00U
#define COLOR_GREEND   0xFF008000U
#define COLOR_RED         0xFFFF0000U
#define COLOR_REDD       0xFF800000U
#define COLOR_YELLOW   0xFFFFFF00U
#define COLOR_YELLOWD 0xFF808000U
#define COLOR_SNOW      0xFFEEE9E9U
#define COLOR_SNOWD    0xFF8B8989U
#define COLOR_SILVER     0xFFC0C0C0U
#define COLOR_GRAYL     0xFFBEBEBEU
#define COLOR_GRAY       0xFF808080U
#define COLOR_GRAY_ARSENIC 0xFF3B444BU
#define COLOR_GRAYD     0xFF303030U
#define COLOR_TEAL       0xFF00FFFFU
#define COLOR_TEALD     0xFF008080U
#define COLOR_PURPLE   0xFFFF00FFU
#define COLOR_PURPLED 0xFF800080U
#define COLOR_LAVENDER_BLUSH 0xEEE0E5U
#define COLOR_BLACK      0xFF000000U

#elif  RGB565

#define COLOR_WHITE      uint16_t(0xFFFFU)
#define COLOR_BLUE        uint16_t(0x001FU)
#define COLOR_BLUED      uint16_t(0x0010U)
#define COLOR_GREEN      uint16_t(0x07E0U)
#define COLOR_GREEND    uint16_t(0x0400U)
#define COLOR_RED          uint16_t(0xF800U)
#define COLOR_REDD        uint16_t(0x8000U)
#define COLOR_YELLOW    uint16_t(0xFFE0U)
#define COLOR_YELLOWD  uint16_t(0x8400U)
#define COLOR_SNOW       uint16_t(0xEF5DU)
#define COLOR_SNOWD     uint16_t(0x8C51U)
#define COLOR_SILVER      uint16_t(0xC618U)
#define COLOR_GRAYL      uint16_t(0xBDF7U)
#define COLOR_GRAY        uint16_t(0x8410U)
#define COLOR_GRAY_ARSENIC uint16_t(0x3A29U)
#define COLOR_GRAYD      uint16_t(0x3186U)
#define COLOR_TEAL        uint16_t(0x0410U)
#define COLOR_TEALD      uint16_t(0x0410U)
#define COLOR_PURPLE    uint16_t(0xF81FU)
#define COLOR_PURPLED  uint16_t(0x8010U)
#define COLOR_LAVENDER_BLUSH uint16_t(0xEF1CU)
#define COLOR_BLACK      uint16_t(0x0000U)

#endif

}
#endif /* GUI_COMMON_H_ */
