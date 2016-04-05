#ifndef CONFIG_H
#define CONFIG_H

#if __GNUC__
    #if __unix || __unix__
        #define PLATFORM_POSIX 1

        #if __linux
            #define PLATFORM_LINUX 1
        #else
            #error Unknown OS
        #endif
    #endif
#endif

#ifdef _MSC_VER
    #define PLATFORM_WIN32 1

    #ifdef _WIN64
        #define PLATFORM_WIN64 1
    #endif
#endif

#endif // CONFIG_H
