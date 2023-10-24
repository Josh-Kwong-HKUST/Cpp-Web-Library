#include "../include/ClientSocket.h"

int main(int argc, char** argv){
    ClientSocket client = ClientSocket(argv[1], atoi(argv[2])); // 47.243.244.116:8888
    client.connectToServer();
}