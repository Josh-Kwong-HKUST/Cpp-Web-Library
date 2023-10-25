#include "Client.h"

Client::Client(Socket* sock){
    this->sock = sock;
}

Client::Client(){}

Client::~Client(){
    delete sock;
}

Socket* Client::getSocket(){
    return this->sock;
}
