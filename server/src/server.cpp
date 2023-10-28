#include "../include/Server.h"

int main(int argc, char** argv){
    Server* server = new Server(atoi(argv[1]));
    server->Init();
    delete server;
}