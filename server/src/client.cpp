#include "../include/Socket.hpp"

int main(int argc, char** argv){
    Socket client = Socket(argv[1], atoi(argv[2])); // 47.243.244.116:8888
    client.connectToServer();
}