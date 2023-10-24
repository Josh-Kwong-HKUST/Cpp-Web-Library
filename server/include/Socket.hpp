#pragma once

#include <netinet/in.h>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <string.h>
#include <iostream>
#include <sys/types.h>

using namespace std;

class Socket{
    private:
        int sockFd;
        struct sockaddr_in* addr;
        char ip[16];
        uint16_t port;
    public:
        int getSockfd(){
            return sockFd;
        }
        sockaddr_in* getAddr(){
            return this->addr;
        }
        char* getIP(){
            return this->ip;
        }
        uint16_t getPort(){
            return this->port;
        }
        Socket(const char* ip, uint16_t port){
            memset(addr, 0, sizeof(sockaddr_in));
            addr->sin_addr.s_addr = inet_addr(ip);
            addr->sin_port = htons(port);
            addr->sin_family = AF_INET;
            strcpy(this->ip, ip);
            this->port = port;
        }
};
