#ifndef ADDITIONAL_H
#define ADDITIONAL_H

#include "font/ifont.h"
#include "gui/system/singleton.h"
#include "common.h"

class Additional
{
    public:
        explicit Additional(u_color bg = {0x00E8F6FAU});
        virtual ~Additional() {}

    public:
        virtual void updateGeometry() = 0;

        inline const IFont &font() const
        {
            return *pFont;
        }

        inline const u_color background() const
        {
            return m_background;
        }
        void setBackground(const u_color bg);

        inline bool isVisible() const
        {
            return visible;
        }

    protected:
        void setVisible(bool visible);

    protected:
        const IFont *pFont;
        u_color m_background;
        bool visible;
};

#endif // ADDITIONAL_H
