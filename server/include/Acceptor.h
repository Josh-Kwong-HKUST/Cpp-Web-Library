#pragma once

#include "Channel.h"
#include "Eventloop.h"
#include "Socket.h"
#include <functional>

class Acceptor{
private:
    Eventloop* loop;
    Socket* sock;
    Channel* acceptChannel;
    std::function<void(Socket*)> newConnectionCallback;
public:
    Acceptor(Eventloop* _loop, int port);
    ~Acceptor();
    void acceptConnection();
    void setNewConnectionCallback(std::function<void(Socket*)> cb);
};