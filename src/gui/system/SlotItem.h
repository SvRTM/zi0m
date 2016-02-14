/*
 * SlotItem.h
 *
 *  Created on: 7 февр. 2016 г.
 *      Author: Artem.Smirnov
 */

#ifndef GUI_SYSTEM_SLOTITEM_H_
#define GUI_SYSTEM_SLOTITEM_H_

#include <functional>

template<typename Signature>
class SlotItem;
template<typename Result, typename ... Args>
class SlotItem<Result(Args ...)>
{
        using Slot = std::function<Result(Args ...)>;

    public:
        explicit SlotItem(SlotItem<Result(Args ...)> *_pPrev, Slot &_cbFunc)
                : cbFunc(_cbFunc), pNext(nullptr), pPrev(_pPrev)
        {
        }
        ~SlotItem()
        {
            if (pNext == nullptr)
                return;

            delete pNext;
            pNext = nullptr;
        }
        SlotItem(const SlotItem&) = delete; //запретить копирование
        void operator=(const SlotItem&) = delete; //запретить присваивание

        SlotItem<Result(Args ...)> * next() const
        {
            return pNext;
        }
        void setNext(SlotItem<Result(Args ...)> *pNextItem)
        {
            this->pNext = pNextItem;
        }
        SlotItem<Result(Args...)> * prev() const
        {
            return pPrev;
        }
        void setPrev(SlotItem<Result(Args ...)> *pPrevItem)
        {
            this->pPrev = pPrevItem;
        }
        Slot &Func()
        {
            return cbFunc;
        }

    private:
        Slot cbFunc;
        SlotItem<Result(Args ...)> *pNext;
        SlotItem<Result(Args ...)> *pPrev;
};

#endif /* GUI_SYSTEM_SLOTITEM_H_ */
