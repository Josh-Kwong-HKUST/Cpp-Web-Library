#include "../include/Server.h"
#include "../include/Client.h"
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
    for (auto entry: mapIdToClient)  delete entry.second;
    delete acceptor;
    delete threadPool;
    for (auto subReactor: subReactors) delete subReactor;
}

void Server::addClient(Client *client){
    this->mapIdToClient[client->getAccountId()] = client;
    this->currentNumConnections++;
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

void Server::forwardMessage(int cli_fd, char buffer[BUFFER_SIZE + 7]){
    Message* msg = new Message(buffer);
    int toId = msg->getToId();
    /*
        999 means broadcast
        server broadcast the message to all clients
    */
    if (toId == 999){
        for (auto client : this->mapIdToClient){
            int targetFd = client.second->getSocket()->getSockfd();
            if (targetFd == cli_fd) continue;
            printf("Broadcasting message from %d to %d\n", msg->getFromId(), client.first);
            printf("Content: %s\n", msg->getContent());
            if(send(targetFd, buffer, BUFFER_SIZE + 7, 0) == -1)
                printf("=====Error: Failed to send message to client %d! Errno: %s=====\n", targetFd, strerror(errno));
        }
    }
    else if (toId == 998){   // 998 means this is a request to server, server needs to respond the online list
        string onlineList = "Current online: ";
        for (auto client : this->mapIdToClient){
            onlineList += to_string(client.first) + " ";
        }
        onlineList += "\0";
        cout << onlineList.c_str() << "\n";
        Client* fromClient = mapIdToClient[msg->getFromId()];
        Message* msg_ = new Message(998, fromClient->getAccountId());
        char* content = msg_->getContent();
        memcpy(content, onlineList.c_str(), onlineList.length());
        char buffer[BUFFER_SIZE + 7];
        msg_->serializeMessage(buffer);
        send(fromClient->getSocket()->getSockfd(), buffer, BUFFER_SIZE + 7, 0);
        delete msg_;
    }
    else if(toId >= 100 && toId < 998){ //private chat
        if (mapIdToClient.find(toId) == mapIdToClient.end()){
            printf("-----System message: Forwarding target id = %d not found!-----\n", toId);
            return;
        }
        Client* toClient = mapIdToClient[toId];
        int targetFd = toClient->getSocket()->getSockfd();
        send(targetFd, buffer, BUFFER_SIZE + 7, 0);
    }
    delete msg;
}

void Server::handleReadEvent(Client* client){
    int sockfd = client->getSocket()->getSockfd();
    char buf[BUFFER_SIZE + 7];
    while(true){
        bzero(&buf, sizeof(buf));
        ssize_t bytes_read = recv(sockfd, buf, sizeof(buf), 0);
        if(bytes_read > 0){
            this->forwardMessage(sockfd, buf);
        } else if(bytes_read == -1 && errno == EINTR){  //client interrupted. continue reading
            printf("continue reading\n");
            continue;
        } else if(bytes_read == -1 && ((errno == EAGAIN) || (errno == EWOULDBLOCK))){//non-blocking IO, no more data to read
            printf("finish reading once, errno: %d\n", errno);
            break;
        } else if(bytes_read == 0){  //EOF, client disconnected
            printf("EOF, user %d disconnected\n", client->getAccountId());
            close(sockfd);   //closing a socket will automatically remove it from epoll
            break;
        }
    }
}