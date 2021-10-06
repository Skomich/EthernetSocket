#pragma once

#include "stdafx.h"
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <unistd.h>
#include <cstring>

#define sockaddr_st sockaddr_in //На случай если понадобится смена на что-то другое везде

#if defined(__APPLE__)
    #define ADDR_LOOPBACK INADDR_LOOPBACK
    #define ADDR_ANY INADDR_ANY
#elif defined(WIN32)
    //
#endif

enum class CONNECTION_ERROR {
    NO_OPERATION = -1,  //-1 еще не использовался
    SUCCESS,            //0 success operation
    SOCKET_CREATE,      //1 socket creating error
    BIND_ERROR,         //2 socket binding error
    CONNECT_ERROR,      //3 connecing error
    ACCEPT_ERROR,       //4 no accepted
    UNDEFINED,          //5 unknown error
    BAD_SOCKET          //6 socket have been no created
};

enum class SOCKET_DOMAIN_TYPE {
     INET               //AF_INET
    ,INET6              //AF_INET6
#if defined(AF_UNIX) || defined(AF_LOCAL)
    ,LOCAL            //AF_UNIX/AF_LOCAL
#endif
};

enum class SOCKET_TYPE {
    TCP,                //SOCK_STREAM
    UDP,                //SOCK_DGRAM
    RAW                 //SOCK_RAW (для работы с "голыми" пакетами)
};

class ISocket {
protected:
    TSOCKET m_socket = -1;
    sockaddr_st m_addr;
    
    int m_last_error = -1;
    
    virtual sockaddr_st CreateAddr(DWORD ip, WORD port) = 0;
    CONNECTION_ERROR SetLastError(CONNECTION_ERROR er) {m_last_error = static_cast<int>(er); return er;}
public:
    ISocket& operator = (const TSOCKET& right) {this->m_socket = right; return *this;}
    ISocket& operator = (const ISocket& right) {m_socket = right.m_socket; m_addr = right.m_addr; return *this;}
    ~ISocket() {std::cout << "socket.h: destruct\n";}
    ISocket(TSOCKET sock) {std::cout << "socket.h: param. constr\n"; m_socket = sock;}
    ISocket() {std::cout << "socket.h: def. constr\n"; m_socket = -1;}
    
    TSOCKET GetSocket() {return m_socket;}
    sockaddr_st GetAddr() {return m_addr;}
    void SetAddr(struct sockaddr_st addrIn) {m_addr = addrIn;}
    
    bool isNoValidSocket() {return m_socket < 0 ? true : false;}
    int GetLastError() {return m_last_error;}
    
    virtual CONNECTION_ERROR Create(SOCKET_DOMAIN_TYPE, SOCKET_TYPE, int) = 0;
    virtual CONNECTION_ERROR Bind(DWORD addr = 0, WORD port = 0) = 0;
    virtual CONNECTION_ERROR Connect(DWORD addr, WORD port) = 0;
    virtual CONNECTION_ERROR Listen(DWORD clientCount) = 0;
    virtual CONNECTION_ERROR Accept(TSOCKET &socketAccepted) = 0;
    virtual CONNECTION_ERROR Accept(ISocket &socketAccepted) {return this->Accept(socketAccepted.m_socket);}
    virtual CONNECTION_ERROR Close() = 0;
    //доделать
    virtual CONNECTION_ERROR Send(char* buffer, DWORD buffer_size) = 0;
    virtual CONNECTION_ERROR Recv(char* buffer, DWORD buffer_size) = 0;
};
