#include "Socket.h"
#include "Client.h"
#include "Epoll.h"
#include <sys/socket.h>
#include <vector>
#include <unordered_map>
#include "Channel.h"
#include "Eventloop.h"
#include "Acceptor.h"

class Server{
    private:
        std::unordered_map<int, Client*> mapIdToClient;
        int currentNumConnections;
        Eventloop* loop;
        Acceptor* acceptor;
    public:
        Server(uint16_t port, Eventloop* lp);
        ~Server(){
            for (auto entry: mapIdToClient)  delete entry.second;
            delete acceptor;
        }
        void Init();
        void addClient(Client* client);
        void forwardMessage(int cli_fd, char buffer[BUFFER_SIZE + 7]);
        void newConnection(Socket* serverSock);
        void handleReadEvent(Client* client);
};