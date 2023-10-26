#include "Client.h"
#include "Message.h"

Client::Client(Socket* sock, int id): sock(sock), accountId(id){}

Client::Client(){}

Client::~Client(){
    delete sock;
}

Socket* Client::getSocket(){
    return this->sock;
}

int Client::getAccountId(){
    return this->accountId;
}

void Client::setAccountId(int id){
    this->accountId = id;
}

void Client::sendMessage(int id){
    Message* msg = new Message(this->getAccountId(), id);
    cout << "Enter message content: \n";
    msg->inputContent();
    char buffer[BUFFER_SIZE + 7];
    bzero(buffer, (BUFFER_SIZE + 7)*sizeof(char));
    msg->serializeMessage(buffer);
    write(this->getSocket()->getSockfd(), buffer, BUFFER_SIZE + 7);
    delete msg;
}

void Client::recvMessage(){
    char buffer[BUFFER_SIZE];
    bzero(buffer, BUFFER_SIZE*sizeof(char));
    recv(this->getSocket()->getSockfd(), buffer, BUFFER_SIZE, 0);
    Message* msg = new Message(buffer);
    cout << "-----Message from use (id = " << msg->getFromId() << "): " << msg->getContent() << "\n";
    delete msg;
}

void Client::connect(){
    this->sock->connectToServer();
}