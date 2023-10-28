#include "Client.h"
#include "Message.h"

/* start routine for thread*/
void* recvMessage(void* arg){
    while(true){
        Client* client = (Client*)arg;
        char buffer[BUFFER_SIZE + 7];
        bzero(buffer, (BUFFER_SIZE + 7)*sizeof(char));
        recv(client->getSocket()->getSockfd(), buffer, BUFFER_SIZE + 7, 0);
        Message* msg = new Message(buffer);
        if(msg->getFromId() == 998) cout << "=====" << msg->getContent() << "=====" << "\n";
        else cout << "User " << msg->getFromId() << ": " << msg->getContent() << "\n";
        delete msg;
    }
    return nullptr;
}

void* sendMessage(void* arg){
    while(true){
        Client* client = (Client*)arg;
        Message* msg = new Message(client->getAccountId(), 999);
        msg->inputContent();
        if (strcmp(msg->getContent(), "/list") == 0)    msg->setToId(998);
        char buffer[BUFFER_SIZE + 7];
        bzero(buffer, (BUFFER_SIZE + 7)*sizeof(char));
        msg->serializeMessage(buffer);
        send(client->getSocket()->getSockfd(), buffer, BUFFER_SIZE + 7, 0);
        delete msg;
    }
    return nullptr;
}
Client::Client(Socket* sock, int id): sock(sock), accountId(id){}

Client::Client(){}

Client::~Client(){
    pthread_join(*this->threadRecv, NULL);
    pthread_join(*this->threadSend, NULL);
    delete this->threadRecv;
    delete this->threadSend;
    delete sock;
}

void Client::Init(){
    this->threadRecv = new pthread_t;
    this->threadSend = new pthread_t;
    pthread_create(this->threadRecv, NULL, recvMessage, (void*)this);
    pthread_create(this->threadSend, NULL, sendMessage, (void*)this);
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

void Client::connect(){
    cout << "Hi User " << this->accountId << "\n";
    this->sock->connectToServer();
}
