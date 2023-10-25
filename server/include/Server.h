#include "Socket.h"
#include "Client.h"
#include "Epoll.h"
#include <sys/socket.h>
#include <vector>

class Server{
    private:
        Socket* sock;
        std::vector<Client*> clients;
        int MAXCONNECTION = SOMAXCONN;
        Epoll* ep;
        int currentNumConnections;
    public:
        Server(const char* ip, uint16_t port, int maxConnection = SOMAXCONN){
            cout << "-----System message: Creating Server instance...-----\n";
            this->sock = new Socket(ip, port);
            this->MAXCONNECTION = maxConnection;
            this->ep = new Epoll();
            this->currentNumConnections = 0;
            cout << "-----System message: Server instance created!-----\n";
        }
        ~Server(){
            for (auto client: clients)  delete client;
            delete sock;
            delete ep;
        }
        void Init();
        void addClient(Client* client);
};