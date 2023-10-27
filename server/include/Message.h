#pragma once

#define BUFFER_SIZE 1024
#include <string.h>

class Message {
    private:
        int fromId;
        int toId;
        char* content;

    public:
        Message(int fromId, int toId);
        Message(char* buffer);  //deserialize
        ~Message();
        void serializeMessage(char buffer[BUFFER_SIZE + 7]);
        void inputContent();
        int getFromId();
        int getToId();
        char* getContent();
};

