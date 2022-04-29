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
unsigned int port = 456;
std::string ip;

int main(int argc, char* argv[])
{
    
    Logger *logger = new OutStreamLogger();
    
    logger->Log("Start prog");
    
    Socket sock(SOCKET_DOMAIN_TYPE::INET, SOCKET_TYPE::TCP, 0);
    if(sock.isNoValidSocket())
    {
        std::cout << "Socket create error: " << sock.GetLastError() << '\n';
        return 1;
    }
    
    std::cout << "Socket created: " << sock.GetSocket() << '\n';
    
    std::string param = "";
    
    if(argc >= 2)
    {
        param = argv[1];
    } else
        param = "server";
    
    if(param == "client")
    {
        //start client module
        
        sock.Connect(ADDR_LOOPBACK, port);
        if(sock.GetLastError()) {
            std:: cout << "Connect error: " << sock.GetLastError() << '\n';
            return 2;
        }
        
        std::cout << "Client: Connected\n";
        
        send(sock.GetSocket(), message, sizeof(message), 0);
        
        //send(iSocket, message, sizeof(message), 0);
        std::cout << "Client: Message send: " << message << '\n';
        //end client module
    }
    else if (param == "server")
    {
        //start server module
        
        sock.Bind(ADDR_ANY, port);
        if(sock.GetLastError()) {
            std::cout << "Can't bind socket: " << sock.GetLastError() << ", errno: " << errno << '\n';
            std::cout << strerror(errno) << '\n';
            return 2;
        }
        
        std::cout << "Server: Socket binded\n";
        
        sock.Listen(1);
        std::cout << "Server: Start listen\n";
        
        int /*sock,*/ iMessageSize, clientCount = 0;
        Socket sock_t{};
        buf = new unsigned char[sizeof(message)];
        
        do
        {
            sock.Accept(sock_t);
            
            if(sock_t.isNoValidSocket())
            {
                std::cout << "No valid accepted socket: " << sock.GetLastError() << '\n';
                return 3;
            }
            std::cout << "Server: Client accepted\n";
            
            while(true)
            {
                iMessageSize = recv(sock_t.GetSocket(), buf, 1024, 0);
                if(iMessageSize <= 0)
                { //connect or socket closed
                    std::cout << "Connect or socket closed.\n";
                    break;
                }
                std::cout << "Server: Message get: " << buf << '\n';
                send(sock_t.GetSocket(), buf, iMessageSize, 0);
                ++clientCount;
            }
            std::cout << "Тут должен закрыться сокет\n";;
        } while(false);
        std::cout << "sock_t close\n";
        
        //end server module
    } else {
        std::cout << "Bad input\n";
        return 2;
    }
    
    logger->Log("End program");
}
