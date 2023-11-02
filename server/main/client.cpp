#include "../include/Connection.h"
#define HELP "=============================================\n/login {your name} {your password}     to login your account\n/register {your name} {your password}  to register a new account\n/help                                  to show this message\n=============================================\n"

int main(int argc, char** argv){
    // 47.243.244.116:8888
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
    delete clientSocket,
    delete conn;
}