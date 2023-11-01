#include "Socket.h"
#include "Client.h"
#include "Epoll.h"
#include "Channel.h"
#include "Eventloop.h"
#include "Acceptor.h"
#include "Connection.h"
#include "ThreadPool.h"

#include <sys/socket.h>
#include <vector>
#include <unordered_map>
#include <map>

class Server{
    private:
        Eventloop* mainReactor;
        std::vector<Eventloop*> subReactors;
        ThreadPool* threadPool;
        std::unordered_map<int, Client*> mapIdToClient;
        int currentNumConnections;
        Acceptor* acceptor;
        std::map<int, Connection*> connections;
    public:
        Server(uint16_t port, Eventloop* reactor);
        ~Server();
        void Init();
        void addClient(Client* client);
        void forwardMessage(int cli_fd, char buffer[BUFFER_SIZE + 7]);
        void newConnection(Socket* sock);
        void deleteConnection(Socket* sock);
        void handleReadEvent(Client* client);
};