#pragma once
#include "Socket.h"

class Client{
    private:
        Socket* sock;
        char username[21];
        char password[21];
    public:
        Client(Socket* sock);
        Client();
        ~Client();
        Socket* getSocket();
};