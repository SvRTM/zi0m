#ifndef SIMBASE_H
#define SIMBASE_H

#include "gui/common.h"

#include <iostream>
#include <signal.h>

class SimBase
{
    public:
        SimBase() = default;
        virtual ~SimBase() = default;

    public:
        virtual void exec() = 0;

    protected:
        template<typename ... Args>
        void Panic(const char *pFormat, Args... args)
        {
            size_t length = snprintf(nullptr, 0, pFormat, args...);
            std::string buf;
            buf.resize(length);
            snprintf(&buf[0], length + 1, pFormat, args...);
            std::cerr << buf << std::endl;

#if __unix || __unix__
            signal(SIGILL, SIG_DFL);
            signal(SIGSEGV, SIG_DFL);
            signal(SIGBUS, SIG_DFL);
            signal(SIGFPE, SIG_DFL);
#endif

#ifdef PLATFORM_WIN32
#   ifdef __NOASSEMBLY__
#       if defined(PLATFORM_WINCE) || defined(WIN64)
            DebugBreak();
#       endif
#   else
#       if defined(_DEBUG) && defined(CPU_X86)
#           ifdef COMPILER_MSC
            _asm int 3
#           endif
#           ifdef COMPILER_GCC
            asm("int $3");
#           endif
#       endif
#   endif
#endif
#ifdef _DEBUG
            __BREAK__;
#endif
        }

        inline void clearMessage()
        {
            msg = {zi0m::EventType::None, 0};
        }

    protected:
        zi0m::Message msg = {zi0m::EventType::None, 0};
};

#endif // SIMBASE_H
