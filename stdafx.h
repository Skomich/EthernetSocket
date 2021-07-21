#pragma once

#if defined(__APPLE__)
    #define DWORD __uint32_t
    #define WORD __uint16_t
#elif define(MSVC)
    #define DWORD unsigned long
#endif
