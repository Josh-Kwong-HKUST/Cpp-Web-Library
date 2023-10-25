#include "Server.h"

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
                Client* client = new Client(new Socket(cli_sock));
                this->addClient(client);
                cout << "-----System message: new client connected to server! Current online: " << this->currentNumConnections << "-----\n";
            }
        }
    }
}

void Server::addClient(Client *client){
    this->clients.push_back(client);
    this->currentNumConnections++;
    this->ep->addSocket(client->getSocket());
}