#include "Connection.h"

Connection::Connection(Eventloop* _loop, Socket* _sock): loop(_loop), sock(_sock){
    channel = new Channel(loop, sock->getSockfd());
    auto cb = std::bind(&Connection::job, this);
    channel->setCallback(cb);
    channel->enableReading();
    channel->setInEpoll();
}

Connection::~Connection(){
    delete channel;
    delete sock;
}

void Connection::setDeleteConnectionCallback(std::function<void(Socket*)> cb){
    deleteConnectionCallback = cb;
}

void Connection::job(){
    cout << "Connection doing its job!" << endl;
}