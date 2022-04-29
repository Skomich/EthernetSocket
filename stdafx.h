#pragma once

//Use the T-prefix if the definition can already be defined in one of the systems

#define LOG_LEVEL_1 //вывод в стандартный поток/файл все что находится в socket.h и в socket_impl .h/.cpp
//#define LOG_LEVEL_2 //?
//#define LOG_LEVEL_3 //?

//common for BSD, Linux and MacOS
#if defined(__APPLE__) || defined(unix)
    #define TUNIX
    #define TSOCKET int
    #define THANDLE int
#endif

#if defined(__APPLE__)                      //for MacOS
    #define TAPPLE
    #define QWORD __uint64_t
    #define DWORD __uint32_t
    #define WORD __uint16_t

#elif defined(unix)                         //for BSD and Linux
    #define TLINUX
    #define QWORD unsigned long    //need to check
    #define DWORD unsigned int    //need to check
    #define WORD unsigned short     //need to check

#elif defined(_WIN32)                       //for Windows x86 and x86_64
    #define TWINDOWS
    #define DWORD unsigned long
    #define WORD unsigned short
    #define TSOCKET SOCKET
    #define THANDLE HANDLE
#endif
