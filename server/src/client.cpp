#include "../include/Socket.h"
#include "../include/Client.h"

int main(int argc, char** argv){
    // 47.243.244.116:8888
    Client* client = new Client(new Socket(argv[1], atoi(argv[2])), atoi(argv[3]));
    cout << "Connecting to server...\n";
    client->connect();
    client->Init();
    delete client;
}