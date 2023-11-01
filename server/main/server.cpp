#include "../include/Server.h"

int main(int argc, char** argv){
    Eventloop* loop = new Eventloop();
    Server* server = new Server(atoi(argv[1]), loop);
    server->onConnect([](Connection* conn){     // customize service logic
        printf("-----Service Logic!-----\n");
    });
    loop->loop();
    delete server;
    delete loop;
    return 0;
}