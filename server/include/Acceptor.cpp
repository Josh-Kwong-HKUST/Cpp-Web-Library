#include "Acceptor.h"
#include "Socket.h"

Acceptor::Acceptor(Eventloop* _loop, int port): loop(_loop){
    this->sock = new Socket("0.0.0.0", port);
    this->sock->bindSocketToAddr();
    this->sock->listenToPort();
    this->sock->setNonBlocking();
    this->acceptChannel = new Channel(this->loop, this->sock->getSockfd());
    auto cb = std::bind(&Acceptor::acceptConnection, this);
    /*
        when a new connection is established(readable events on acceptChannel),
        the acceptor will call Acceptor::acceptConnection
    */
    this->acceptChannel->setCallback(cb);
    this->acceptChannel->enableReading();
}

Acceptor::~Acceptor(){
    delete sock;
    delete acceptChannel;
}

void Acceptor::acceptConnection(){
    int clientSockFd = this->sock->acceptClient();
    Socket* clientSock = new Socket(clientSockFd);
    clientSock->setNonBlocking();
    newConnectionCallback(clientSock);
}

void Acceptor::setNewConnectionCallback(std::function<void(Socket*)> cb){
    newConnectionCallback = cb;
}