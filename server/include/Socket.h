#pragma once

#include <netinet/in.h>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <string.h>
#include <iostream>
#include <sys/types.h>
#include <fcntl.h>

using namespace std;
typedef struct sockaddr_in sockaddr_in;

class Socket{
    private:
        int sockFd;
        struct sockaddr_in addr;
        char ip[16];
        uint16_t port;
        int MAXCONNECTION = SOMAXCONN;
    public:
        /* constructor */
        Socket(const char* ip, uint16_t port){
            cout << "-----System message: Socket creating on "<< ip << ":" << port<< "...-----\n";
            bzero(&addr, sizeof(addr));
            strcpy(this->ip, ip);
            this->port = port;
            addr.sin_addr.s_addr = inet_addr(ip);
            addr.sin_port = htons(port);
            addr.sin_family = AF_INET;
            sockFd = socket(AF_INET, SOCK_STREAM, 0);
        }
        Socket(int fd):sockFd(fd){};
        
        int getSockfd();
        void setNonBlocking();
        sockaddr_in getAddr();
        char* getIP();
        uint16_t getPort();
        void connectToServer();
        void bindSocketToAddr();
        void listenToPort();
        int acceptClient();
};
