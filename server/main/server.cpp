#include "../include/Server.h"

int main(int argc, char** argv){
    Eventloop* loop = new Eventloop();
    Server* server = new Server(atoi(argv[1]), loop);
    loop->loop();
    delete server;
    delete loop;
    return 0;
}