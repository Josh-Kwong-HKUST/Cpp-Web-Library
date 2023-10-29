#include "Acceptor.h"

Acceptor::Acceptor(Eventloop* _loop, int port): loop(_loop){
    this->sock = new Socket("0.0.0.0", port);
    this->sock->bindSocketToAddr();
    this->sock->listenToPort();
    this->sock->setNonBlocking();
    this->acceptChannel = new Channel(this->loop, this->sock->getSockfd());
    auto cb = std::bind(&Acceptor::acceptConnection, this);
    this->acceptChannel->setCallback(cb);
    this->acceptChannel->enableReading();
}

Acceptor::~Acceptor(){
    delete sock;
    delete acceptChannel;
}

void Acceptor::acceptConnection(){
    newConnectionCallback(this->sock);
}

void Acceptor::setNewConnectionCallback(std::function<void(Socket*)> cb){
    newConnectionCallback = cb;
}