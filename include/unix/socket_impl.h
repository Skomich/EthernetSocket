#pragma once

#include "../socket.h"

class Socket : public ISocket {
protected:
    sockaddr_st CreateAddr(DWORD ip, WORD port);
public:
    Socket();
    Socket(TSOCKET sock);
    ~Socket() {std::cout << "unix/socket_impls.h: destruct"; Close();}
    virtual CONNECTION_ERROR Create(SOCKET_DOMAIN_TYPE domain, SOCKET_TYPE type, int protocol);
    virtual CONNECTION_ERROR Close();
    
    virtual CONNECTION_ERROR Bind(DWORD ip, WORD port);
    virtual CONNECTION_ERROR Connect(DWORD ip, WORD port);
    virtual CONNECTION_ERROR Listen(DWORD clientCount);
    virtual CONNECTION_ERROR Accept(TSOCKET &socketAccepted);
    
    //доделать
    virtual CONNECTION_ERROR Send(char* buffer, DWORD buffer_size);
    virtual CONNECTION_ERROR Recv(char* buffer, DWORD buffer_size);
};
