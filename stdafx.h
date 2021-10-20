#pragma once

#define LOG_LEVEL_1 //вывод в стандартный поток все что находится в socket.h и в socket_impl .h/.cpp
//#define LOG_LEVEL_2 //?
//#define LOG_LEVEL_3 //?

#if defined(__APPLE__)
    #define QWORD __uint64_t
    #define DWORD __uint32_t
    #define WORD __uint16_t
    #define TSOCKET int
    #define THANDLE void*
#elif defined(UNIX)
    //
#elif define(WIN32)
    #define DWORD unsigned long
    #define WORD unsigned short
    #define TSOCKET SOCKET
    #define THANDLE HANDLE
#endif
