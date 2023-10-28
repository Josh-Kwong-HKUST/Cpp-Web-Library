#include "../include/Socket.h"
#include "../include/Client.h"

int main(int argc, char** argv){
    // 47.243.244.116:8888
    char* id;
    cout << "Type your account id in 3 digit: \n";
    cin.getline(id, 4);
    Client* client = new Client(new Socket(argv[1], atoi(argv[2])), atoi(id));
    cout << "Connecting to server...\n";
    client->connect();
    write(client->getSocket()->getSockfd(), id, 4);
    client->Init();
    delete client;
}