#include "Socket.h"
#include "Client.h"
#include "Epoll.h"
#include <sys/socket.h>
#include <vector>
#include <unordered_map>

class Server{
    private:
        Socket* sock;
        std::unordered_map<int, Client*> mapIdToClient;
        int MAXCONNECTION = SOMAXCONN;
        Epoll* ep;
        int currentNumConnections;
    public:
        Server(uint16_t port, int maxConnection = SOMAXCONN){
            cout << "-----System message: Creating Server instance...-----\n";
            this->sock = new Socket("0.0.0.0", port);
            this->MAXCONNECTION = maxConnection;
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
        void forwardMessage(int cli_fd);
};