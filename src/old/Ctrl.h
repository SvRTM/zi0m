/*
 * Ctrl.h
 *
 *  Created on: 25 янв. 2016 г.
 *      Author: Artem.Smirnov
 */

//Современные компиляторы поддерживают #pragma once.
//
// НЕПРАВИЛЬНЫЙ вариант:
//#ifndef PROJECT_HEADERNAME
//#define PROJECT_HEADERNAME
//.
//.
//.
//#endif /* PROJECT_HEADERNAME */
//
//
// Вместо него используем
//#pragma once
#ifndef GUI_CTRL_H_
#define GUI_CTRL_H_

#include "../gui/InputDevice.h"
//#include "../win32-test/Application.h"

#include <vector>
#include <functional>

class Application;
class Ctrl
{
    public:
        Ctrl(Application *app);
        virtual ~Ctrl();

    public:
        void addDevice(InputDevice *device);
        std::vector<InputDevice *> getDevices();
        void quantum();
        void paint();
        //void operator()();

    private:
        Application *pApp;
        std::function<void(_MSG)> callback;

        std::vector<InputDevice *> devices;
};

#endif /* GUI_CTRL_H_ */
