#include "../include/Server.h"

int main(int argc, char** argv){
    Server* server = new Server(argv[1], atoi(argv[2]));
    server->Init();
    delete server;
}