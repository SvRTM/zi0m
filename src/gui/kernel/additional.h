#ifndef ADDITIONAL_H
#define ADDITIONAL_H

#include "gui/text/font/ifont.h"
#include "gui/kernel/singleton.h"
#include "gui/common.h"

namespace zi0m
{
class Additional
{
    public:
#ifdef RGB888
        explicit Additional(u_color bg = {0x00E8F6FAU});
#elif  RGB565
        explicit Additional(u_color bg = {0xEFBFU});
#endif
        virtual ~Additional() {}

    public:
        virtual void updateAllPosition() = 0;

        inline const IFont &font() const
        {
            return *pFont;
        }

        inline const u_color background() const
        {
            return m_background;
        }
        void setBackground(const u_color bg);

        // This property holds whether the widget is enabled.
        inline bool isEnabled() const
        {
            return enabled;
        }

    protected:
        inline void refresh(bool refresh = true)
        {
            m_refresh = refresh;
        }

    protected:
        const IFont *pFont;
        bool m_refresh = true;
        bool enabled = true;
    private:
        u_color m_background;
};
}
#endif // ADDITIONAL_H
