#pragma once

#if defined(__APPLE__)
    #define DWORD __uint32_t
    #define WORD __uint16_t
    #define TSOCKET int
#elif define(MSVC)
    #define DWORD unsigned long
    #define WORD unsigned short
    #define TSOCKET SOCKET
#endif
