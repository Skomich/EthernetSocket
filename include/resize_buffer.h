#pragma once

#include "stdafx.h"
#include <string.h>

class ResizeBuffer {
private:
    unsigned char* pBuff = nullptr;
    DWORD dwBufferSize = 0;
public:
    ResizeBuffer() {};
    //буфер размером dwDataSize будет пустым
    ResizeBuffer(DWORD dwDataSize);
    //копирует из pData, а не инициализирует этой перменной
    ResizeBuffer(unsigned char* pData, DWORD dwDataSize);
    
    //может вернуть nullptr
    unsigned char* GetBuffer() {return pBuff;}
    DWORD GetBufferSize() {return dwBufferSize;}
    
    //не уменьшает буфер
    bool Resize(DWORD dwNewSize);
    
    //добавить в конец
    bool AddToBack(unsigned char* pData, DWORD dwDataSize);
    //добавить в начало (буфер будет переинициализирован всегда)
    bool AddToStart(unsigned char* pData, DWORD dwDataSize);
};
