#pragma once
#include "Socket.hpp"
#include <iostream>
#include <sys/socket.h>

class ServerSocket: public Socket{
    /*
        base class member:
            sockFd: server socket file descriptor
            addr: information of server including ip and the port to listen
        derive class member:
            clientFd: keep record of the connected client socket file descriptor
            MAXCONNECTION: the capacity of maximum connected clients at a moment
    */
    private:
        int clientFd;

    public:
        const int MAXCONNECTION = SOMAXCONN;
        ServerSocket(const char* ip = "0.0.0.0", uint16_t port = 8888):Socket(ip, port){
            cout << "-----System message: ServerSocket creating...-----\n";
            this->clientFd = -1;
        }
        int getClientFd(){
            return this->clientFd;
        }
        void bindSocketToAddr();
        void listenToPort();
        void acceptClient();
        void Init();
};