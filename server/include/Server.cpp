#include "Server.h"
#include <iostream>
#include <errno.h>

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
    int toId = msg->getToId();
    /*
        999 means broadcast
        server broadcast the message to all clients
    */
    if (toId == 999){
        for (auto client : this->mapIdToClient){
            int targetFd = client.second->getSocket()->getSockfd();
            if (targetFd == cli_fd) continue;
            cout << "Broadcasting message from "<< msg->getFromId() << " to " << client.first << "\n";
            cout << "Content: " << msg->getContent() << "\n";
            if(write(targetFd, buffer, BUFFER_SIZE + 7) == -1){
                cout << "=====Error: Failed to send message to client " << targetFd << " Errno: " << errno << "=====\n";
            }
        }
    }
    else{   // private chat
        if (mapIdToClient.find(toId) == mapIdToClient.end()){
            cout << "-----System message: Forwarding target id = " << toId << " not found!-----\n";
            return;
        }
        Client* toClient = mapIdToClient[toId];
        int targetFd = toClient->getSocket()->getSockfd();
        write(targetFd, buffer, BUFFER_SIZE + 7);
    }
    delete msg;
}