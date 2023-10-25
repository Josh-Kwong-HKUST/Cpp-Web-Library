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
        static int numOfConnections;
        int getSockfd(){
            return sockFd;
        }
        void setNonBlocking(){
            fcntl(this->sockFd, F_SETFL, fcntl(sockFd, F_GETFL) | O_NONBLOCK);
        }
        sockaddr_in getAddr(){
            return this->addr;
        }
        char* getIP(){
            return this->ip;
        }
        uint16_t getPort(){
            return this->port;
        }
        Socket(const char* ip, uint16_t port){
            cout << "-----System message: Socket creating on "<< ip << ":" << port<< "...-----\n";
            bzero(&addr, sizeof(addr));
            strcpy(this->ip, ip);
            this->port = port;
            addr.sin_addr.s_addr = inet_addr(ip);
            addr.sin_port = htons(port);
            addr.sin_family = AF_INET;
            sockFd = socket(AF_INET, SOCK_STREAM, 0);
            numOfConnections = 0;
        }
        void connectToServer(){
            sockaddr_in addr = this->getAddr();
            if(connect(this->getSockfd(), (sockaddr*)&addr, sizeof(addr)) == -1){
                cerr << "=====Error: Failed to connect to " << this->getIP() << ":" << this->getPort() << std::endl;
                exit(-1);
            }
            cout << "System message: -----You are online!-----\n";
        }
        void bindSocketToAddr(){
            sockaddr_in addr = this->getAddr();
            if (bind(this->getSockfd(), (sockaddr*)&addr, sizeof(addr)) == -1){
                cerr << "=====Error: Server failed to bind the socket to the address=====\n";
                exit(-1);
            }
            cout << "-----System message: Server successfully binded the socket to the address!-----\n";
        }

        void listenToPort(){
            if (listen(this->getSockfd(), this->MAXCONNECTION) == -1){
                cerr << "=====Error: Server failed to listen to port " << this->getPort() << "=====\n";
                exit(-1);
            }
            cout << "-----System message: Server successfully listened to port " << this->getPort() << "!-----\n";
        }

        int acceptClient(){ // return clientFd
            sockaddr_in clientSock;
            socklen_t lenClientSock = sizeof(clientSock);
            bzero(&clientSock, lenClientSock);
            int clientFd = accept(this->getSockfd(), (sockaddr*)&clientSock, &lenClientSock);
            if(clientFd == -1){
                cerr << "=====Error: Server failed to accept clients=====\n";
                exit(-1);
            }
            cout << "-----System message: new client connected to server! Current online: " << this->numOfConnections << "-----\n";
            return clientFd;
        }
};
