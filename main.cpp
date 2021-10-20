#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <unistd.h>
#include <iostream>
#include "resize_buffer.h"
#include "connect_base.h"
#include "logger/logger.h"

char message[] = "Hello world!\n";
unsigned char *buf;
unsigned int port = 80;
std::string ip;

int main(int argc, char* argv[]) {
    
    Logger *logger = new ConsoleLogger();
    
    logger->Log("Start program");
    
    Socket sock;
    sock.Create(SOCKET_DOMAIN_TYPE::INET, SOCKET_TYPE::TCP, 0);
    if(sock.isNoValidSocket()) {
        std::cout << "Socket create error: " << sock.GetLastError() << '\n';
        return 1;
    }
    
    /*int iSocket;
    struct sockaddr_in addr;
    
    iSocket = socket(AF_INET, SOCK_STREAM, 0);
    if(iSocket < 0) {
        std::cout << "Socket create error: " << errno << '\n';
        return 1;
    }*/
    
    std::cout << "Socket created: " << sock.GetSocket() << '\n';
    
    /*addr.sin_family = AF_INET;
    addr.sin_port = htons(port);*/
    
    std::string param = "";
    
    if(argc >= 2) {
        param = argv[1];
    } else
        param = "server";
    
    if(param == "client") {
        //start client module
        
        sock.Connect(ADDR_LOOPBACK, port);
        if(sock.GetLastError()) {
            std:: cout << "Connect error: " << sock.GetLastError() << '\n';
            return 2;
        }
        
        /*if(!ip.empty())
            addr.sin_addr.s_addr = inet_addr(ip.c_str());
        else
            addr.sin_addr.s_addr = htonl(INADDR_LOOPBACK);
        
        if(connect(iSocket, (struct sockaddr*) &addr, sizeof(addr)) < 0) {
            std::cout << "Connect error: " << errno << '\n';
            return 3;
        }*/
        
        std::cout << "Client: Connected\n";
        
        send(sock.GetSocket(), message, sizeof(message), 0);
        
        //send(iSocket, message, sizeof(message), 0);
        std::cout << "Client: Message send: " << message << '\n';
        //end client module
    } else if (param == "server") {
        //start server module
        
        sock.Bind(ADDR_ANY, port);
        if(sock.GetLastError()) {
            std::cout << "Cant bind socket: " << sock.GetLastError() << '\n';
            return 2;
        }
        
        /*addr.sin_addr.s_addr = htonl(INADDR_ANY);
        
        if(bind(iSocket, (struct sockaddr*) &addr, sizeof(addr)) < 0) {
            std::cout << "Bind socket error: " << errno << '\n';
            return 3;
        }*/
        
        std::cout << "Server: Socket binded\n";
        
        //listen(iSocket, 1);
        sock.Listen(1);
        std::cout << "Server: Start listen\n";
        
        int /*sock,*/ iMessageSize, clientCount = 0;
        Socket sock_t{};
        buf = new unsigned char[sizeof(message)];
        
        do {
            sock.ISocket::Accept(sock_t);
            
            if(sock_t.isNoValidSocket()) {
                std::cout << "No valid accepted socket: " << sock.GetLastError() << '\n';
                return 3;
            }
            //sock = accept(iSocket, NULL, NULL);
//            if(sock < 0) {
//                std::cout << "Accept error: " << errno << '\n';
//                return 4;
//            }
            std::cout << "Server: Client accepted\n";
            
            while(true) {
                iMessageSize = recv(sock_t.GetSocket(), buf, 1024, 0);
                if(iMessageSize <= 0) { //connect or socket closed
                    std::cout << "Connect or socket closed.\n";
                    break;
                }
                std::cout << "Server: Message get: " << buf << '\n';
                send(sock_t.GetSocket(), buf, iMessageSize, 0);
                ++clientCount;
                
//                iMessageSize = recv(sock, buf, 1024, 0);
//                if(iMessageSize <= 0) //connect or socket closed
//                    break;
//                std::cout << "Server: Message get: " << buf << '\n';
//
//                send(sock, buf, iMessageSize, 0);
//                std::cout << "Message send\n";
//
//                ++clientCount;
            }
            std::cout << "Тут должен закрыться сокет\n";
//            close(sock);
        } while(false);
        std::cout << "sock_t close\n";
        
        //end server module
    } else {
        std::cout << "Bad input\n";
        return 2;
    }
    std::cout << "sock.close()\n";
    sock.Close();
    std::cout << "sock.close() after\n";
//    close(iSocket);
    
    logger->Log("End program");
}
