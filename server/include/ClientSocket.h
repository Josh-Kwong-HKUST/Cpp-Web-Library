#pragma once
#include "Socket.hpp"

class ClientSocket: public Socket{
    /*
        base class member:
            sockFd: the client socket file descriptor
            addr: infomation of the target server including ip, port
        Note that the user does not need to specify ip and port for the client
    */
    public:
        ClientSocket(const char* ip, uint16_t port = 8888):Socket(ip, port){
            cout << "-----System message: ClientSocket creating...\n-----";
        }
        void connectToServer();
};