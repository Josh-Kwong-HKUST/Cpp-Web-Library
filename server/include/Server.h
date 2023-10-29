#include "Socket.h"
#include "Client.h"
#include "Epoll.h"
#include <sys/socket.h>
#include <vector>
#include <unordered_map>
#include "Channel.h"
#include "Eventloop.h"

class Server{
    private:
        Socket* sock;
        std::unordered_map<int, Client*> mapIdToClient;
        Epoll* ep;
        int currentNumConnections;
        Eventloop* loop;
    public:
        Server(uint16_t port, Eventloop* lp){
            cout << "-----System message: Creating Server instance...-----\n";
            this->sock = new Socket("0.0.0.0", port);
            this->loop = lp;
            this->ep = new Epoll();
            this->currentNumConnections = 0;
            cout << "-----System message: Server instance created!-----\n";
        }
        ~Server(){
            for (auto entry: mapIdToClient)  delete entry.second;
            delete sock;
            delete ep;
        }
        void Init();
        void addClient(Client* client);
        void forwardMessage(int cli_fd, char buffer[BUFFER_SIZE + 7]);
        void newConnection();
        void handleReadEvent(Client* client);
};