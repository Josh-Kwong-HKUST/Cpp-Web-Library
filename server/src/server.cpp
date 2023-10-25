#include "../include/ServerSocket.h"
#include "../include/Epoll.h"

int main(int argc, char** argv){
    ServerSocket* server = new ServerSocket(argv[1], atoi(argv[2]));
    server->Init();
    Epoll* ep = new Epoll();
    ep->Init(server);
    while (true){
        std::vector<epoll_event> activeEvents = ep->poll();
        for (auto event : activeEvents){
            if (event.data.fd == server->getSockfd()){
                server->acceptClient();
            }
        }
    }
    delete server;
    delete ep;
}