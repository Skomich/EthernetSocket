#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <unistd.h>
#include <iostream>

char message[] = "Hello world!\n";
char buf[sizeof(message)];
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
    
    std::cout << "1) Socket created\n";
    
    addr.sin_family = AF_INET;
    addr.sin_port = htons(port);
    
    std::string param = "";
    
    if(argc >= 2) {
        param = argv[1];
    } else
        param = "client";
    
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
        
        std::cout << "Connected\n";
        
        send(iSocket, message, sizeof(message), 0);
        std::cout << "Message send: " << message << '\n';
        
        recv(iSocket, buf, sizeof(buf), 0);
        std::cout << "Message get: " << buf << '\n';
        //end client module
    } else if (param == "server") {
        //start server module
        addr.sin_addr.s_addr = htonl(INADDR_ANY);
        
        if(bind(iSocket, (struct sockaddr*) &addr, sizeof(addr)) < 0) {
            std::cout << "Bind socket error: " << errno << '\n';
            return 3;
        }
        std::cout << "Socket binded\n";
        
        listen(iSocket, 1);
        std::cout << "Start listen\n";
        
        int sock, iMessageSize;
        
        while(true) {
            sock = accept(iSocket, NULL, NULL);
            if(sock < 0) {
                std::cout << "Accept error: " << errno << '\n';
                return 4;
            }
            std::cout << "Client accepted\n";
            
            while(true) {
                iMessageSize = recv(sock, buf, 1024, 0);
                if(iMessageSize <= 0) //connect or socket closed
                    break;
                std::cout << "Message get: " << buf << '\n';
                
                send(sock, buf, iMessageSize, 0);
                std::cout << "Message send\n";
                
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
