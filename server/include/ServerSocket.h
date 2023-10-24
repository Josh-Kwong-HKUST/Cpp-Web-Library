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
        static int MAXCONNECTION;
    public:
        ServerSocket(const char* ip = "0.0.0.0", uint16_t port = 8888, int MAXCONNECTION = SOMAXCONN):Socket(ip, port){
            this->clientFd = 0;
            this->MAXCONNECTION = MAXCONNECTION;
        }
        int getClientFd(){
            return this-> clientFd;
        }
        int getMaxConnection(){
            return this->MAXCONNECTION;
        }
        void bindSocketToAddr();
        void listenToPort();
        void acceptClient();
        void Init();
};