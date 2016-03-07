/*
 * Signal.h
 *
 *  Created on: 7 февр. 2016 г.
 *      Author: Artem.Smirnov
 */

#ifndef GUI_SYSTEM_SIGNAL_H_
#define GUI_SYSTEM_SIGNAL_H_

#include "SlotItem.h"
#include <functional>

template<typename Signature>
class Signal;
template<typename Result, typename ... Args>
class Signal<Result(Args ...)>
{
        using Slot = std::function<Result(Args ...)>;

    public:
        explicit Signal()
                : pRoot(nullptr), pLastItem(nullptr)
        {
        }
        ~Signal()
        {
            if (pRoot == nullptr)
                return;
            delete pRoot;
            pRoot = nullptr;
            pLastItem = nullptr;
        }
        Signal(const Signal&) = delete; //запретить копирование
        void operator=(const Signal&) = delete; //запретить присваивание

        SlotItem<Result(Args...)> *connect(Slot callback)
        {
            if (pRoot == nullptr)
            {
                pLastItem = pRoot = new SlotItem<Result(Args...)>(nullptr,
                        callback);
                return pRoot;
            }

            /*SlotItem<Result(Args...)> *next, *prev = pFirstItem;
             do
             {
             next = prev->next();
             if (next == nullptr)
             break;
             prev = next;
             } while (true);

             next = new SlotItem<Result(Args...)>(prev, callback);
             prev->setNext(next);
             return next;*/
            SlotItem<Result(Args...)> *prev = pLastItem;
            pLastItem = new SlotItem<Result(Args...)>(prev, callback);
            prev->setNext(pLastItem);
            return pLastItem;
        }
        void disconnect(SlotItem<Result(Args...)> *id)
        {
            if (pRoot == nullptr)
                return;

            SlotItem<Result(Args...)> *current;
            for (current = pRoot; current != id; current = current->next())
                if (current == nullptr)
                    return;
            /*
             SlotItem<Result(Args...)> *current = pFirstItem;
             do
             {
             if (current == id)
             break;
             current = current->next();
             if (current == nullptr)
             return;
             } while (true);
             */
            SlotItem<Result(Args...)> *prev, *next;
            prev = current->prev();
            next = current->next();
            if (prev == next)
            {
                delete pRoot;
                pRoot = pLastItem = nullptr;
                return;
            }

            if (prev != nullptr)
            {
                prev->setNext(next);
                current->setPrev(nullptr);
            }
            if (next != nullptr)
            {
                next->setPrev(prev);
                current->setNext(nullptr);
            }

            delete current;
        }
        Result emit(Args ... args)
        {
            if (pRoot == nullptr)
                return Result();

            SlotItem<Result(Args...)> *next, *prev = pRoot;
            while ((next = prev->next()) != nullptr)
            {
                prev->Func()(args ...);
                prev = next;
            }
            /*
             do
             {
             next = prev->next();
             if (next == nullptr)
             break;
             prev->Func()(args ...);
             prev = next;
             } while (true);
             */

            return prev->Func()(args ...);
        }

    private:
        SlotItem<Result(Args...)> *pRoot;
        SlotItem<Result(Args...)> *pLastItem;
};

#endif /* GUI_SYSTEM_SIGNAL_H_ */
