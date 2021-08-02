#pragma once

#include "stdafx.h"
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <unistd.h>
#include <cstring>

enum class CONNECTION_ERROR {
    SOCKET_CREATE,      //socket creating error
    BIND_ERROR,         //socket binding error
    CONNECT_ERROR,      //connecing error
    ACCEPT_ERROR,       //no accepted
    UNDEFINED,          //unknown error
    SUCCESS,            //function is success
    BAD_SOCKET          //socket have been no created
};

class ISocket {
protected:
    TSOCKET m_socket = -1;
    sockaddr_in m_addr;
    
    virtual sockaddr_in CreateAddr(DWORD ip, WORD port) = 0;
public:
    ISocket& operator = (const TSOCKET& right) {this->m_socket = right; return *this;}
    ~ISocket() {if(m_socket < 0) return; else ::close(m_socket);}
    ISocket(TSOCKET sock) {m_socket = sock;}
    
    TSOCKET GetSocket() {return m_socket;}
    sockaddr_in GetAddr() {return m_addr;}
    void SetAddr(struct sockaddr_in addrIn) {m_addr = addrIn;}
    
    bool isNoValidSocket() {return m_socket < 0 ? true : false;}
    
    virtual CONNECTION_ERROR Create() = 0;
    virtual CONNECTION_ERROR Bind(DWORD addr = 0, WORD port = 0) = 0;
    virtual CONNECTION_ERROR Connect(DWORD addr, WORD port) = 0;
    virtual CONNECTION_ERROR Listen(DWORD clientCount) = 0;
    virtual CONNECTION_ERROR Accept(ISocket &socketAccepted) = 0;
};
