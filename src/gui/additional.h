#ifndef COM_H
#define COM_H

#include "font/ifont.h"
#include "gui/system/singleton.h"
#include "common.h"

class Additional
{
    public:
        explicit Additional();
        virtual ~Additional() {}

    public:
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

    private:
        u_color m_background;
        bool visible;
};

#endif // COM_H
