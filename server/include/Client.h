#pragma once
#include "Socket.h"
#include "Message.h"
#include <pthread.h>

class Client{
    private:
        Socket* sock;
        char username[21];
        char password[21];
        int accountId;
        pthread_t* threadRecv;
        pthread_t* threadSend;
    public:
        Client(Socket* sock, int id);
        Client();
        ~Client();
        Socket* getSocket();
        int getAccountId();
        void setAccountId(int id);
        void connect();
        void Init();
};