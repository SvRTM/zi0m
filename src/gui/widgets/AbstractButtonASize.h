/*
 * Copyright © 2016 Artem Smirnov
 * All right reserved.
 * Author: Artem Smirnov <msvrtm@gmail.com>
 * License: http://www.gnu.org/licenses/gpl.txt
 */

#ifndef ABSTRACTBUTTONASIZE_H
#define ABSTRACTBUTTONASIZE_H

#include "AbstractButton.h"

namespace zi0m
{
class AbstractButtonASize : public AbstractButton
{
    public:
        explicit AbstractButtonASize(Point pos, const Rect &border, Widget *const parent);
        virtual ~AbstractButtonASize() = default;

    public:
        void setAutoSize(bool autoSize);

    protected:
        void init();

    private:
        void autoSize();
        void p_setSize() override;
        void p_setFont() override;
        void p_setText() override;
        void p_updateAllPosition() override;

    protected:
        static constexpr uint8_t marginLeftRight = 5;

    private:
        bool m_autoSize = true;
};
}
#endif // ABSTRACTBUTTONASIZE_HH
