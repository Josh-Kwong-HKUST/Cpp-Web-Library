#include "../include/Socket.h"

int main(int argc, char** argv){
    Socket client = Socket(argv[1], atoi(argv[2])); // 47.243.244.116:8888
    client.connectToServer();
    char buf[1024];
    while(true){
        bzero(buf, sizeof(buf));
        std::cin.getline(buf, sizeof(buf));
        if (strcmp(buf, "exit") == 0){
            break;
        }
        send(client.getSockfd(), buf, sizeof(buf), 0);
        bzero(buf, sizeof(buf));
        recv(client.getSockfd(), buf, sizeof(buf), 0);
        std::cout << buf << std::endl;
    }
}