#pragma once

#include "../socket.h"

class Socket : public ISocket
{
protected:
    sockaddr_st CreateAddr(DWORD ip, WORD port);
public:
    Socket();
    Socket(SOCKET_DOMAIN_TYPE domain, SOCKET_TYPE type, int protocol);
    Socket(TSOCKET sock);
    ~Socket() {std::cout << "unix/socket_impls.h: destruct"; Close();}
    CONNECTION_ERROR Create(SOCKET_DOMAIN_TYPE domain, SOCKET_TYPE type, int protocol);
    CONNECTION_ERROR Close();
    
    CONNECTION_ERROR Bind(DWORD ip, WORD port);
    CONNECTION_ERROR Connect(DWORD ip, WORD port);
    CONNECTION_ERROR Listen(DWORD clientCount);
    CONNECTION_ERROR Accept(TSOCKET &socketAccepted);
    CONNECTION_ERROR Accept(Socket &socketAccepted) {return ISocket::Accept(socketAccepted);}
    
    //доделать
    CONNECTION_ERROR Send(char* buffer, DWORD buffer_size);
    CONNECTION_ERROR Recv(char* buffer, DWORD buffer_size);
};
