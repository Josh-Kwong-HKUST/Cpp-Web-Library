#include "../include/Connection.h"
#include <thread>

#define HELP "\n\n==========================================================\n/login {your name} {your password}     to login your account\n/register {your name} {your password}  to register a new account\n/help                                  to show this message\n==========================================================\n\n"

int main(int argc, char** argv){
    Socket* clientSocket = new Socket(argv[1], atoi(argv[2]));
    clientSocket->connectToServer();
    Connection* conn = new Connection(nullptr, clientSocket);   // client connection does not have event loop
    while (true){
        printf(HELP);
        conn->setWriteBufferGetline();
        if(conn->getWriteBuffer()->equal("/help")) continue;
        conn->write();
        conn->read();
        if(conn->getReadBuffer()->equal("OK")){
            printf("Login success!\n");
            break;
        }
        printf("%s\n",conn->getReadBuffer()->toStr());
    }
    // service logic
    std::thread readThread([&conn](){
        while (true){
            conn->read();
            printf("%s\n", conn->getReadBuffer()->toStr());
        }
    });
    std::thread writeThread([&conn](){
        while (true){
            conn->setWriteBufferGetline();
            conn->write();
        }
    });
    while (true){
        if (conn->getState() == Connection::State::Closed){
            printf("Connection closed\n");
            break;
        }
    }
    delete clientSocket,
    delete conn;
}