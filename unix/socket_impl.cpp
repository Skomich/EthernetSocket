#include <iostream>
#include "socket_impl.h"

Socket::Socket() : ISocket() {}

Socket::Socket(SOCKET_DOMAIN_TYPE domain, SOCKET_TYPE type, int protocol) : ISocket()
{
    Create(domain, type, protocol);
}

CONNECTION_ERROR Socket::Create(SOCKET_DOMAIN_TYPE domain, SOCKET_TYPE type, int protocol)
{
    std::cout << "Socket create start\n";
    m_socket = ::socket(PF_INET, SOCK_STREAM, 0);
    if(m_socket < 0)
    {
        SetLastError(CONNECTION_ERROR::SOCKET_CREATE);
    }
    
    return SetLastError(CONNECTION_ERROR::SUCCESS);
}

CONNECTION_ERROR Socket::Close()
{
    std::cout << "Socket close start\n";
    if(m_socket < 0)
    {
        SetLastError(CONNECTION_ERROR::BAD_SOCKET);
    }
    
    ::close(m_socket);
    
    return SetLastError(CONNECTION_ERROR::SUCCESS);
}

sockaddr_st Socket::CreateAddr(DWORD ip, WORD port)
{
    sockaddr_st addr;
    
    std::memset(&addr, 0, sizeof(addr));
    addr.sin_addr.s_addr = htonl(ip);
    addr.sin_family = AF_INET;
    addr.sin_port = htons(port);
#ifdef __APPLE__
    addr.sin_len = sizeof(addr);
#endif
    return addr;
}

CONNECTION_ERROR Socket::Bind(DWORD ip, WORD port)
{
    if(m_socket < 0)
    {
        return SetLastError(CONNECTION_ERROR::BAD_SOCKET);
    }
    
    m_addr = CreateAddr(ip, port);
    
    if(::bind(m_socket, reinterpret_cast<sockaddr*>(&m_addr), sizeof(m_addr)) < 0)
    {
        return SetLastError(CONNECTION_ERROR::BIND_ERROR);
    }
    
    return SetLastError(CONNECTION_ERROR::SUCCESS);
}

CONNECTION_ERROR Socket::Connect(DWORD ip, WORD port)
{
    if(m_socket < 0)
        return SetLastError(CONNECTION_ERROR::BAD_SOCKET);
    
    sockaddr_st addr = CreateAddr(ip, port);
    if(::connect(m_socket, reinterpret_cast<sockaddr*>(&addr), sizeof(addr)) < 0)
    {
        return SetLastError(CONNECTION_ERROR::CONNECT_ERROR);
    }
    
    return SetLastError(CONNECTION_ERROR::SUCCESS);
}

CONNECTION_ERROR Socket::Listen(DWORD client_count)
{
    if(m_socket < 0)
        return SetLastError(CONNECTION_ERROR::BAD_SOCKET);
    
    ::listen(m_socket, client_count);
    return SetLastError(CONNECTION_ERROR::SUCCESS);
}

CONNECTION_ERROR Socket::Accept(TSOCKET &socketAccepted)
{
    if(m_socket < 0)
        return SetLastError(CONNECTION_ERROR::CONNECT_ERROR);
    
    struct sockaddr addr;
    DWORD addr_size;
    socketAccepted = ::accept(m_socket, &addr, &addr_size);
    //in next path addr will be save in accepted socket if needed
    
    if(socketAccepted < 0 || sizeof(addr) != addr_size)
        return SetLastError(CONNECTION_ERROR::ACCEPT_ERROR);
    
    return SetLastError(CONNECTION_ERROR::SUCCESS);
}

CONNECTION_ERROR Socket::Send(char* buffer, DWORD buffer_size)
{
    return CONNECTION_ERROR::NO_OPERATION;
}

CONNECTION_ERROR Socket::Recv(char* buffer, DWORD buffer_size)
{
    return CONNECTION_ERROR::NO_OPERATION;
}
