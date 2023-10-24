#include "ClientSocket.h"

void ClientSocket::connectToServer(){
    sockaddr_in addr = this->getAddr();
    if(connect(this->getSockfd(), (sockaddr*)&addr, sizeof(addr)) == -1){
        cerr << "=====Error: Client failed to connect to " << this->getIP() << ":" << this->getPort() << std::endl;
        exit(-1);
    }
    cout << "System message: -----You are online!-----\n";
}