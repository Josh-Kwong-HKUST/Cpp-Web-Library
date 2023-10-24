#include "ServerSocket.h"


void ServerSocket::bindSocketToAddr(){
    struct sockaddr_in* addr = this->getAddr();
    if (bind(this->getSockfd(), (sockaddr*)addr, sizeof(*addr)) == -1){
        cerr << "=====Error: Server failed to bind the socket to the address=====\n";
        exit(-1);
    }
}

void ServerSocket::listenToPort(){
    if (listen(this->getSockfd(), this->getMaxConnection()) == -1){
        cerr << "=====Error: Server failed to listen to port " << this->getPort() << "=====\n";
        exit(-1);
    }
}

void ServerSocket::acceptClient(){
    sockaddr_in clientSock;
    socklen_t lenClientSock = sizeof(clientSock);
    memset(&clientSock, 0, lenClientSock);
    this->clientFd = accept(this->getSockfd(), (sockaddr*)&clientSock, &lenClientSock);
    if(this->clientFd == -1){
        cerr << "=====Error: Server failed to accept clients=====\n";
        exit(-1);
    }
    cout << "-----System message: 1 client connected to server!\n-----";
}

void ServerSocket::Init(){
    bindSocketToAddr();
    listenToPort();
    acceptClient();
}