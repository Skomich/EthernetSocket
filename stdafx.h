#pragma once

#if defined(__APPLE__)
    #define DWORD unsigned int
#elif define(MSVC)
    #define DWORD unsigned long
#endif
