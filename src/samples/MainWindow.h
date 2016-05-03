/*
 * MainWindow.h
 *
 *  Created on: 3 февр. 2016 г.
 *      Author: Artem.Smirnov
 */

#ifndef MAINWINDOW_H_
#define MAINWINDOW_H_

#include "gui/widgets/Widget.h"

#include "AbstractBody.h"

#include <vector>

using namespace zi0m;

class MainWindow final : public Widget
{
    public:
        explicit MainWindow();
        virtual ~MainWindow() {}

    private:
        void paint(MonitorDevice *const pMonitorDevice) override;
        void event(const EventType type, const Point &pos) override;

        void setupUi();

    private:
        std::vector<AbstractBody *> bodys;

        inline const Rect &Border() const
        {
            return zeroBorder;
        }

    private:
        // # # # # # # # # # # # # # # # #
        class Header final : public Widget
        {
            public:
                Header(Widget *m_parent);
                virtual ~Header() {}

            private:
                void paint(MonitorDevice *const pMonitorDevice) override;
                void event(const EventType type, const Point &pos) override;

            private:
                uint8_t iWidget = 0;
                AbstractBody  *pBodyWidget = nullptr;
                uint8_t nFont = 0;
                std::vector<std::pair<const IFont *, std::u16string>> fonts;

                inline const Rect &Border() const
                {
                    return zeroBorder;
                }
        };

        class Body final : public Widget
        {
            public:
                Body(Widget *m_parent);
                virtual ~Body() {}

            private:
                void paint(MonitorDevice *const pMonitorDevice) override;
                void event(const EventType type, const Point &pos) override;

                inline const Rect &Border() const
                {
                    return zeroBorder;
                }
        };
};

#endif /* MAINWINDOW_H_ */
