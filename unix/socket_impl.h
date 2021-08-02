#pragma once

#include "../socket.h"

class SocketTCP : public ISocket {
protected:
    sockaddr_in CreateAddr(DWORD ip, WORD port);
public:
    SocketTCP();
    SocketTCP(TSOCKET sock);
    ~SocketTCP();
    virtual CONNECTION_ERROR Create();
    virtual CONNECTION_ERROR Bind(DWORD ip, WORD port);
    virtual CONNECTION_ERROR Connect(DWORD ip, WORD port);
    virtual CONNECTION_ERROR Listen(DWORD clientCount);
    virtual CONNECTION_ERROR Accept(ISocket &socketAccepted);
};
