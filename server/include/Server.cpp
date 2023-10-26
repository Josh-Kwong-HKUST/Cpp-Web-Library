#include "Server.h"
#include <iostream>

void Server::Init(){
    this->sock->bindSocketToAddr();
    this->sock->listenToPort();
    this->ep->addSocket(this->sock);
    cout << "-----System message: Server successfully initialized!-----\n";
    while (true){   // server main loop
        std::vector<epoll_event> activeEvents = ep->poll();
        for (auto event : activeEvents){
            if (event.data.fd == this->sock->getSockfd()){  // new connection
                int cli_sock = this->sock->acceptClient();
                char idBuffer[4];
                read(cli_sock, idBuffer, 4);
                Client* client = new Client(new Socket(cli_sock), atoi(idBuffer));
                this->addClient(client);
                cout << "-----System message: new client connected to server! Current online: " << this->currentNumConnections << "-----\n";
            }
            else if(event.events & EPOLLIN){    // readable event
                int cli_sock = event.data.fd;
                this->forwardMessage(cli_sock);
            }
        }
    }
}

void Server::addClient(Client *client){
    this->mapIdToClient[client->getAccountId()] = client;
    this->currentNumConnections++;
    this->ep->addSocket(client->getSocket());
}

void Server::forwardMessage(int cli_fd){
    char buffer[BUFFER_SIZE + 7];
    read(cli_fd, buffer, BUFFER_SIZE + 7);
    Message* msg = new Message(buffer);
    // cout << "-----System message: Receive message from id = " << msg->getFromId();
    // cout << " content: '" << msg->getContent() << "' to id = " << msg->getToId() << "-----\n";
    int toId = msg->getToId();
    if (mapIdToClient.find(toId) == mapIdToClient.end()){
        cout << "-----System message: Forwarding target id = " << toId << " not found!-----\n";
        return;
    }
    Client* toClient = mapIdToClient[toId];
    int targetFd = toClient->getSocket()->getSockfd();
    write(targetFd, buffer, BUFFER_SIZE + 7);
    delete msg;
}