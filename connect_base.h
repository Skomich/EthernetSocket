#pragma once

#include "stdafx.h"
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <unistd.h>
#include "resize_buffer.h"

#if defined(TUNIX)
    #include "unix/socket_impl.h"
#endif


/*class Connector {
protected:
    CONNECTION_ERROR wLastError;
    virtual CONNECTION_ERROR GetLastError() {return wLastError;}
    virtual int GetLastErrorNo() {return errno;};
public:
    virtual void SendData(ResizeBuffer rBuffer) = 0;
    virtual DWORD ReceiveData(ResizeBuffer& rBuffer) = 0;
};

class TCPConnector : public Connector {
protected:
    virtual bool ConnectTo(DWORD ip, WORD port);
    virtual bool BindAddr(DWORD ip, WORD port);
    virtual bool ListenClients(DWORD client_count);
public:
    virtual void SendData(ResizeBuffer rBuffer) = 0;
    virtual DWORD ReceiveData(ResizeBuffer& rBuffer) = 0;
};

class ServerConnector : public Connector {
protected:
    DWORD ip = 0;
    WORD port = 0;
public:
    virtual void SendData(ResizeBuffer rBuffer) = 0;
    virtual DWORD ReceiveData(ResizeBuffer& rBuffer) = 0;
};

class ClientConnector : public Connector {
protected:
    DWORD ip = 0;
    WORD port = 0;
public:
    virtual void SendData(ResizeBuffer rBuffer) = 0;
    virtual DWORD ReceiveData(ResizeBuffer& rBuffer) = 0;
};

class TCPServer : public ServerConnector {
public:
    virtual void SendData(ResizeBuffer rBuffer);
    virtual DWORD ReceiveData(ResizeBuffer& rBuffer);
};
*/
