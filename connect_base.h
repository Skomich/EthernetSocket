#pragma once

#include "stdafx.h"
#include <sys/types.h>
#include <sys/socket.h>
#include "resize_buffer.h"

#if defined(__APPLE__)
    #include "connect_mac.h"
#elif defined (MSVC)
#endif

class Connector {
public:
    virtual void SendData(ResizeBuffer rBuffer) = 0;
    virtual DWORD ReceiveData(ResizeBuffer& rBuffer) = 0;
};

class TCPConnector {
protected:
    virtual WORD Send(unsigned char* buffer, DWORD size);
    virtual WORD Recv(unsigned char* buffer, DWORD buffer_size);
};

class Server : public Connector {
protected:
    DWORD ip = 0;
    WORD port = 0;
public:
    virtual void SendData(ResizeBuffer rBuffer) = 0;
    virtual DWORD ReceiveData(ResizeBuffer& rBuffer) = 0;
};

class Client : public Connector {
protected:
    DWORD ip = 0;
    WORD port = 0;
public:
    virtual void SendData(ResizeBuffer rBuffer) = 0;
    virtual DWORD ReceiveData(ResizeBuffer& rBuffer) = 0;
};

class TCPServer : public Server {
public:
    virtual void SendData(ResizeBuffer rBuffer);
    virtual DWORD ReceiveData(ResizeBuffer& rBuffer);
};
