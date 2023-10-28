#include "Message.h"
#include <iostream>

Message::Message(int fromId, int toId): fromId(fromId), toId(toId) {
    this->content = new char[BUFFER_SIZE + 1];
    bzero(this->content, (BUFFER_SIZE + 1)*sizeof(char));
}

Message::Message(char* buffer){
    char id[4];
    strncpy(id, buffer, 3);
    this->fromId = atoi(id);
    strncpy(id, buffer + 3, 3);
    this->toId = atoi(id);
    this->content = new char[BUFFER_SIZE + 1];
    bzero(this->content, (BUFFER_SIZE + 1)*sizeof(char));
    strncpy(this->content, buffer + 6, BUFFER_SIZE + 1);
}

void Message::inputContent(){
    std::fgets(this->content, BUFFER_SIZE + 1, stdin);
    this->content[strlen(this->content) - 1] = '\0';
}

Message::~Message(){
    delete[] this->content;
}

void Message::serializeMessage(char buffer[BUFFER_SIZE + 7]){
    std::string s = std::to_string(this->fromId);
    const char* c = s.c_str();
    memcpy(buffer, c, 4);
    s = std::to_string(this->toId);
    c = s.c_str();
    memcpy(buffer + 3, c, 4);
    for (int i = 0; i < BUFFER_SIZE + 1; i++){
        buffer[i + 6] = this->content[i];
    }
}

int Message::getFromId(){
    return this->fromId;
}

int Message::getToId(){
    return this->toId;
}

char* Message::getContent(){
    return this->content;
}

void Message::setToId(int toId){
    this->toId = toId;
}