#include "../include/Server.h"
#include "../include/Message.h"
#include <cstdio>
#include <iostream>
#include <errno.h>

Server::Server(uint16_t port, Eventloop* reactor): mainReactor(reactor), currentNumConnections(0){
    printf("-----System message: Creating Server instance...-----\n");
    this->acceptor = new Acceptor(this->mainReactor, port);
    /*
        bind the callback function to the acceptor
        when a new connection is established, the acceptor will call Server::newConnection    
    */
    auto cb = std::bind(&Server::newConnection, this, std::placeholders::_1);
    this->acceptor->setNewConnectionCallback(cb);
    int size = std::thread::hardware_concurrency();
    this->threadPool = new ThreadPool(size);
    for (int i = 0; i < size; ++i){
        this->subReactors.push_back(new Eventloop());
        this->threadPool->enqueue([this, i](){
            this->subReactors[i]->loop();   // each subReactor starts its event loop
        });
    }
    printf("-----System message: Server instance created!-----\n");
}

Server::~Server(){
    delete acceptor;
    delete threadPool;
    for (auto subReactor: subReactors) delete subReactor;
}

void Server::newConnection(Socket* sock){
    if (sock->getSockfd() == -1){
        printf("=====Error: Failed to accept new connection! Errno: %s=====\n", strerror(errno));
        return;
    }
    int random = sock->getSockfd() % this->subReactors.size();
    Connection *conn = new Connection(this->subReactors[random], sock);
    std::function<void(Socket*)> cb = std::bind(&Server::deleteConnection, this, std::placeholders::_1);
    conn->setOnDeleteConnectionCallback(cb);
    conn->setOnConnectCallback(this->onConnectionCallback);
    connections[sock->getSockfd()] = conn;
    printf("-----System message: new client connected to server! Current online: %d-----\n", ++this->currentNumConnections);
}

void Server::deleteConnection(Socket *sock){
    Connection *conn = connections[sock->getSockfd()];
    connections.erase(sock->getSockfd());
    delete conn;
    printf("-----System message: A client left! Current online: %d-----\n", --this->currentNumConnections);
}

void Server::onConnect(std::function<void(Connection*)> cb){
    this->onConnectionCallback = std::move(cb);
}

void Server::broadcast(const char* msg, int excludeFd){
    for (auto& [fd, conn]: connections){
        if (fd == excludeFd) continue;
        conn->setWriteBuffer(msg);
        conn->write();
    }
}