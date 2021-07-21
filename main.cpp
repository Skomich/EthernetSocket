#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <unistd.h>
#include <iostream>
#include "resize_buffer.h"
#include "connect_base.h"

char message[] = "Hello world!\n";
unsigned char *buf;
int port = 80;
std::string ip;

int main(int argc, char* argv[]) {
    
    
    int iSocket;
    struct sockaddr_in addr;
    
    iSocket = socket(AF_INET, SOCK_STREAM, 0);
    if(iSocket < 0) {
        std::cout << "Socket create error: " << errno << '\n';
        return 1;
    }
    
    std::cout << "Client: Socket created\n";
    
    addr.sin_family = AF_INET;
    addr.sin_port = htons(port);
    
    std::string param = "";
    
    if(argc >= 2) {
        param = argv[1];
    } else
        param = "server";
    
    if(param == "client") {
        //start client module
        if(!ip.empty())
            addr.sin_addr.s_addr = inet_addr(ip.c_str());
        else
            addr.sin_addr.s_addr = htonl(INADDR_LOOPBACK);
        
        if(connect(iSocket, (struct sockaddr*) &addr, sizeof(addr)) < 0) {
            std::cout << "Connect error: " << errno << '\n';
            return 3;
        }
        
        std::cout << "Client: Connected\n";
        
        send(iSocket, message, sizeof(message), 0);
        std::cout << "Client: Message send: " << message << '\n';
        //end client module
    } else if (param == "server") {
        //start server module
        addr.sin_addr.s_addr = htonl(INADDR_ANY);
        
        if(bind(iSocket, (struct sockaddr*) &addr, sizeof(addr)) < 0) {
            std::cout << "Bind socket error: " << errno << '\n';
            return 3;
        }
        std::cout << "Server: Socket binded\n";
        
        listen(iSocket, 1);
        std::cout << "Server: Start listen\n";
        
        int sock, iMessageSize, clientCount = 0;
        buf = new unsigned char[sizeof(message)];
        
        while(true) {
            sock = accept(iSocket, NULL, NULL);
            if(sock < 0) {
                std::cout << "Accept error: " << errno << '\n';
                return 4;
            }
            std::cout << "Server: Client accepted\n";
            
            while(true) {
                iMessageSize = recv(sock, buf, 1024, 0);
                if(iMessageSize <= 0) //connect or socket closed
                    break;
                std::cout << "Server: Message get: " << buf << '\n';
                
                send(sock, buf, iMessageSize, 0);
                std::cout << "Message send\n";
                 
                ++clientCount;
            }
            
            close(sock);
        }
        
        //end server module
    } else {
        std::cout << "Bad input\n";
        return 2;
    }
    
    close(iSocket);
}
