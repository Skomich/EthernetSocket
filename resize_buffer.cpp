#include "resize_buffer.h"

ResizeBuffer::ResizeBuffer(DWORD buffer_size) : dwBufferSize(buffer_size)
{
    Resize(buffer_size);
}

ResizeBuffer::ResizeBuffer(unsigned char* data, DWORD buffer_size) :
dwBufferSize(buffer_size)
{
    AddToBack(data, buffer_size);
}

bool ResizeBuffer::Resize(DWORD buffer_size) {
    if(buffer_size == 0 || buffer_size <= dwBufferSize)
        return true;
    
    try {
        unsigned char* pNewBuf = new unsigned char[buffer_size];
        if(pNewBuf == nullptr)
            return false;
        
        if(pBuff != nullptr) {
            memcpy(pNewBuf, pBuff, dwBufferSize);
            delete[] pBuff;
        }
        
        dwBufferSize = buffer_size;
        pBuff = pNewBuf;
        return true;
    } catch(...) {return false;}
}

bool ResizeBuffer::AddToBack(unsigned char* data, DWORD buffer_size) {
    if(buffer_size == 0)
        return true;
    
    try{
    
    DWORD dwUsed = dwBufferSize;
    
    if(!Resize(buffer_size + dwBufferSize))
        return false;
    
    memcpy(pBuff + dwUsed, data, buffer_size);
    } catch(...) {return false;}
    
    return true;
}

bool ResizeBuffer::AddToStart(unsigned char* data, DWORD buffer_size) {
    if(buffer_size == 0)
        return true;
    
    try {
        DWORD dwUsed = dwBufferSize;
        
        if(!Resize(buffer_size + dwBufferSize))
            return false;
        
        unsigned char* pNewBuf = new unsigned char[dwBufferSize];
        
        memcpy(pNewBuf, data, buffer_size);
        memcpy(pNewBuf + buffer_size, pBuff, dwUsed);
        
        delete[] pBuff;
        pBuff = pNewBuf;
    } catch (...) { return false;}
}
