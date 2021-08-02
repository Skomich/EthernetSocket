#include "socket_impl.h"

CONNECTION_ERROR SocketTCP::Create() {
    m_socket = ::socket(PF_INET, SOCK_STREAM, 0);
    if(m_socket < 0) {
        return CONNECTION_ERROR::SOCKET_CREATE;
    }
    return CONNECTION_ERROR::SUCCESS;
}

sockaddr_in SocketTCP::CreateAddr(DWORD ip, WORD port) {
    sockaddr_in addr;
    
    std::memset(&addr, 0, sizeof(addr));
    addr.sin_addr.s_addr = htonl(ip);
    addr.sin_family = AF_INET;
    addr.sin_port = htons(port);
#ifdef __APPLE__
    addr.sin_len = sizeof(addr);
#endif
    return addr;
}

CONNECTION_ERROR SocketTCP::Bind(DWORD ip, WORD port) {
    if(m_socket < 0)
        return CONNECTION_ERROR::BAD_SOCKET;
    
    if(ip != 0 || port != 0)
        m_addr = CreateAddr(ip, port);
    
    if(::bind(m_socket, reinterpret_cast<sockaddr*>(&m_addr), sizeof(m_addr)) < 0) {
        return CONNECTION_ERROR::BIND_ERROR;
    }
    return CONNECTION_ERROR::SUCCESS;
}

CONNECTION_ERROR SocketTCP::Connect(DWORD ip, WORD port) {
    if(m_socket < 0)
        return CONNECTION_ERROR::BAD_SOCKET;
    
    sockaddr_in addr = CreateAddr(ip, port);
    if(::connect(m_socket, reinterpret_cast<sockaddr*>(&addr), sizeof(addr)) < 0) {
        return CONNECTION_ERROR::CONNECT_ERROR;
    }
    return CONNECTION_ERROR::SUCCESS;
}

CONNECTION_ERROR SocketTCP::Listen(DWORD client_count) {
    if(m_socket < 0)
        return CONNECTION_ERROR::BAD_SOCKET;
    
    ::listen(m_socket, client_count);
    return CONNECTION_ERROR::SUCCESS;
}

CONNECTION_ERROR SocketTCP::Accept(ISocket &socketAccepted) {
    if(m_socket < 0)
        return CONNECTION_ERROR::CONNECT_ERROR;
    
    struct sockaddr addr;
    DWORD addr_size;
    socketAccepted = ::accept(m_socket, &addr, &addr_size);
    //in next path addr will be save in accepted socket if needed
    
    if(socketAccepted.isNoValidSocket() || sizeof(addr) != addr_size)
        return CONNECTION_ERROR::ACCEPT_ERROR;
}

