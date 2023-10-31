#pragma once
#include "Channel.h"
#include "Eventloop.h"
#include "Socket.h"

class Connection{
private:
    Eventloop* loop;
    Socket* sock;
    Channel* channel;
    std::function<void(Socket*)> deleteConnectionCallback;
public:
    Connection(Eventloop* _loop, Socket* _sock);
    ~Connection();
    void setDeleteConnectionCallback(std::function<void(Socket*)> cb);
    void job();
};