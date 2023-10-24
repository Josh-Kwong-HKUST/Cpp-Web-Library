#include "../include/ClientSocket.h"

int main(int argc, char** argv){
    ClientSocket client(argv[1], atoi(argv[2]));
    client.connectToServer();
}