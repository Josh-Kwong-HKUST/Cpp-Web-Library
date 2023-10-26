#pragma once
#include "Socket.h"
#include "Message.h"

class Client{
    private:
        Socket* sock;
        char username[21];
        char password[21];
        int accountId;
    public:
        Client(Socket* sock, int id);
        Client();
        ~Client();
        Socket* getSocket();
        int getAccountId();
        void setAccountId(int id);
        void sendMessage(int id);
        void recvMessage();
        void connect();
};