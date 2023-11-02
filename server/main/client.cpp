#include "../include/Connection.h"

int main(int argc, char** argv){
    // 47.243.244.116:8888
    Socket* clientSocket = new Socket(argv[1], atoi(argv[2]));
    clientSocket->connectToServer();
    Connection* conn = new Connection(nullptr, clientSocket);   // client connection does not have event loop
    while (true){
        if (conn->getState() == Connection::State::Closed){
            printf("Connection closed\n");
            break;
        }
        conn->setWriteBufferGetline();
        conn->write();
        conn->read();
        printf("%s\n", conn->getReadBuffer()->toStr());
    }
}