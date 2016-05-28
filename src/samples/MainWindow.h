/*
 * Copyright © 2016 Artem Smirnov
 * All right reserved.
 * Author: Artem Smirnov <msvrtm@gmail.com>
 * License: http://www.gnu.org/licenses/gpl.txt
 */

#ifndef SAMPLES_MAINWINDOW_H_
#define SAMPLES_MAINWINDOW_H_

#include "gui/widgets/Widget.h"

#include "AbstractBody.h"

#include <vector>

using namespace zi0m;

class MainWindow final : public Widget
{
    public:
        explicit MainWindow();
        virtual ~MainWindow() = default;
    private:
        MainWindow(const MainWindow &) = delete;
        MainWindow &operator=(const MainWindow &) = delete;

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
                virtual ~Header() = default;
            private:
                Header(const Header &) = delete;
                Header &operator=(const Header &) = delete;

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
                virtual ~Body() = default;
            private:
                Body(const Body &) = delete;
                Body &operator=(const Body &) = delete;

            private:
                void paint(MonitorDevice *const pMonitorDevice) override;
                void event(const EventType type, const Point &pos) override;

                inline const Rect &Border() const
                {
                    return zeroBorder;
                }
        };
};

#endif /* SAMPLES_MAINWINDOW_H_ */
