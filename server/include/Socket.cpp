#include "Socket.h"
int Socket::getSockfd(){
    return sockFd;
}
void Socket::setNonBlocking(){
    fcntl(this->sockFd, F_SETFL, fcntl(sockFd, F_GETFL) | O_NONBLOCK);
}
sockaddr_in Socket::getAddr(){
    return this->addr;
}
char* Socket::getIP(){
    return this->ip;
}
uint16_t Socket::getPort(){
    return this->port;
}
void Socket::connectToServer(){
    sockaddr_in addr = this->getAddr();
    if(connect(this->getSockfd(), (sockaddr*)&addr, sizeof(addr)) == -1){
        cerr << "=====Error: Failed to connect to " << this->getIP() << ":" << this->getPort() << std::endl;
        exit(-1);
    }
    cout << "System message: -----You are online!-----\n";
}
void Socket::bindSocketToAddr(){
    sockaddr_in addr = this->getAddr();
    if (bind(this->getSockfd(), (sockaddr*)&addr, sizeof(addr)) == -1){
        cerr << "=====Error: Server failed to bind the socket to the address=====\n";
        exit(-1);
    }
    cout << "-----System message: Server successfully binded the socket to the address!-----\n";
}

void Socket::listenToPort(){
    if (listen(this->getSockfd(), this->MAXCONNECTION) == -1){
        cerr << "=====Error: Server failed to listen to port " << this->getPort() << "=====\n";
        exit(-1);
    }
    cout << "-----System message: Server successfully listened to port " << this->getPort() << "!-----\n";
}

int Socket::acceptClient(){ // return clientFd
    sockaddr_in clientSock;
    socklen_t lenClientSock = sizeof(clientSock);
    bzero(&clientSock, lenClientSock);
    int clientFd = accept(this->getSockfd(), (sockaddr*)&clientSock, &lenClientSock);
    if(clientFd == -1){
        cerr << "=====Error: Server failed to accept clients=====\n";
        exit(-1);
    }
    return clientFd;
}