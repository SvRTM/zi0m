/*
 * Label.h
 *
 *  Created on: 6 марта 2016 г.
 *      Author: Artem.Smirnov
 */

#ifndef SRC_GUI_LABEL_H_
#define SRC_GUI_LABEL_H_

#include "Widget.h"

#include <string>
#include <math.h>
class Label: public Widget
{
    public:
        explicit Label(Widget *parent,
                       Alignment _align = (Alignment) (Alignment::VCenter | Alignment::Left));
        virtual ~Label();

    public:
        void setText(const std::u16string text);
        void setAlignment(Alignment align);

        inline const u_color color() const
        {
            return m_color;
        }
        void setColor(u_color color);

        void paint(MonitorDevice *const pMonitorDevice) override;

    private:
        inline const IFont::CHAR_INFO *descriptor(const wchar_t ch) const
        {
            for (size_t n = 0; n < font().sizeOfBlock; ++n)
            {
                const IFont::BLOCK *block = &font().blocks()[n];
                if (ch >= block->startChar && ch <= block->endChar)
                    return &block->descriptors[ch - block->startChar];
            }

            const IFont::BLOCK *block = &font().blocks()[font().sizeOfBlock - 1];
            return &block->descriptors[0];
        }

        const uint16_t textWidth() const;

        void drawTextMonochrome(MonitorDevice *const pMonitorDevice,
                                const u_color pxColor,
                                const Alignment align);
        void drawText(MonitorDevice *const pMonitorDevice,  const Alignment align,
                      const u_color pxColor);

    private:
        Alignment align;
        std::u16string m_text;
        u_color m_color;
        uint32_t m_textWidth;

        // /////////////////
        // http://stackoverflow.com/questions/3018313/algorithm-to-convert-rgb-to-hsv-and-hsv-to-rgb-in-range-0-255-for-both#6930407
        void rgb2hsv(u_color in , double &h, double &s, double &v)
        {
            double      min, max, delta;
            double r, g, b;
            r = in.uc_color.R / 255.0;
            g = in.uc_color.G / 255.0;
            b = in.uc_color.B / 255.0;

            min = r < g ? r : g;
            min = min  < b ? min  : b;

            max = r > g ? r : g;
            max = max  > b ? max  : b;

            v = max;
            delta = max - min;
            if (delta < 0.00001)
            {
                s = 0;
                h = 0; // undefined, maybe nan?
                return;
            }
            if ( max > 0.0 )  // NOTE: if Max is == 0, this divide would cause a crash
            {
                s = (delta / max);                  // s
            }
            else
            {
                // if max is 0, then r = g = b = 0
                // s = 0, v is undefined
                s = 0.0;
                h = NAN;                            // its now undefined
                return;
            }
            if ( r >= max )                          // > is bogus, just keeps compilor happy
                h = ( g - b ) / delta;        // between yellow & magenta
            else if ( g >= max )
                h = 2.0 + ( b - r ) / delta;  // between cyan & yellow
            else
                h = 4.0 + ( r - g ) / delta;  // between magenta & cyan

            h *= 60.0;                              // degrees

            if ( h < 0.0 )
                h += 360.0;

            return;
        }

        u_color hsv2rgb(double h, double s, double v)
        {
            double      hh, p, q, t, ff;
            long        i;

            double r, g, b;

            if (s <= 0.0)        // < is bogus, just shuts up warnings
            {
                u_color         out;
                out.uc_color.R = v * 255;
                out.uc_color.G = v * 255;
                out.uc_color.B = v * 255;
                return out;
            }
            hh = h;
            if (hh >= 360.0) hh = 0.0;
            hh /= 60.0;
            i = (long)hh;
            ff = hh - i;
            p = v * (1.0 - s);
            q = v * (1.0 - (s * ff));
            t = v * (1.0 - (s * (1.0 - ff)));

            switch (i)
            {
                case 0:
                    r = v;
                    g = t;
                    b = p;
                    break;
                case 1:
                    r = q;
                    g = v;
                    b = p;
                    break;
                case 2:
                    r = p;
                    g = v;
                    b = t;
                    break;

                case 3:
                    r = p;
                    g = q;
                    b = v;
                    break;
                case 4:
                    r = t;
                    g = p;
                    b = v;
                    break;
                case 5:
                default:
                    r = v;
                    g = p;
                    b = q;
                    break;
            }
            u_color         out;
            out.uc_color.R = r * 255;
            out.uc_color.G = g * 255;
            out.uc_color.B = b * 255;
            return out;
        }

        // https://www.programmingalgorithms.com/algorithm/hsl-to-rgb
        void RGBToHSL(u_color  rgb, float &H, float &S, float &L)
        {
            float r = (rgb.uc_color.R / 255.0f);
            float g = (rgb.uc_color.G / 255.0f);
            float b = (rgb.uc_color.B / 255.0f);

            float min = std::min(std::min(r, g), b);
            float max = std::max(std::max(r, g), b);
            float delta = max - min;

            L = (max + min) / 2;

            if (delta == 0)
            {
                H = 0;
                S = 0.0f;
            }
            else
            {
                S = (L <= 0.5) ? (delta / (max + min)) : (delta / (2 - max - min));

                float hue;

                if (r == max)
                    hue = ((g - b) / 6) / delta;
                else if (g == max)
                    hue = (1.0f / 3) + ((b - r) / 6) / delta;
                else
                    hue = (2.0f / 3) + ((r - g) / 6) / delta;

                if (hue < 0)
                    hue += 1;
                if (hue > 1)
                    hue -= 1;

                H = (int)(hue * 360);
            }

            return;
        }

        u_color HSLToRGB(float H, float S, float L)
        {
            uint8_t r = 0;
            uint8_t g = 0;
            uint8_t b = 0;

            if (S == 0)
                r = g = b = (uint8_t)(L * 255);
            else
            {
                float v1, v2;
                float hue = (float)H / 360;

                v2 = (L < 0.5) ? (L * (1 + S)) : ((L + S) - (L * S));
                v1 = 2 * L - v2;

                r = (uint8_t)(255 * HueToRGB(v1, v2, hue + (1.0f / 3)));
                g = (uint8_t)(255 * HueToRGB(v1, v2, hue));
                b = (uint8_t)(255 * HueToRGB(v1, v2, hue - (1.0f / 3)));
            }

            u_color rgb ;
            rgb.uc_color.R = r;
            rgb.uc_color.G = g;
            rgb.uc_color.B = b;
            return rgb;
        }

        float HueToRGB(float v1, float v2, float vH)
        {
            if (vH < 0)
                vH += 1;

            if (vH > 1)
                vH -= 1;

            if ((6 * vH) < 1)
                return (v1 + (v2 - v1) * 6 * vH);

            if ((2 * vH) < 1)
                return v2;

            if ((3 * vH) < 2)
                return (v1 + (v2 - v1) * ((2.0f / 3) - vH) * 6);

            return v1;
        }
};

#endif /* SRC_GUI_LABEL_H_ */
