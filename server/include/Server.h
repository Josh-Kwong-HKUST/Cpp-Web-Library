#include "Socket.h"
#include "Epoll.h"
#include "Channel.h"
#include "Eventloop.h"
#include "Acceptor.h"
#include "Connection.h"
#include "ThreadPool.h"

#include <sys/socket.h>
#include <vector>
#include <map>

class Server{
    private:
        Eventloop* mainReactor;
        std::vector<Eventloop*> subReactors;
        ThreadPool* threadPool;
        int currentNumConnections;
        Acceptor* acceptor;
        std::map<int, Connection*> connections;
        std::function<void(Connection*)> onConnectionCallback;
    public:
        Server(uint16_t port, Eventloop* reactor);
        ~Server();
        void Init();
        void newConnection(Socket* sock);
        void deleteConnection(Socket* sock);
        void onConnect(std::function<void(Connection*)> cb);
        void broadcast(const char* msg, int excludeFd = -1);
        void forwardMsg(const char* msg, int fd);
};