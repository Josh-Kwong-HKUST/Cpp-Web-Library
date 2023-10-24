#include "../include/ServerSocket.h"

int main(int argc, char** argv){
    ServerSocket server = ServerSocket(argv[1], atoi(argv[2]));
    server.Init();
}