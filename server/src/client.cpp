#include "../include/Socket.h"
#include "../include/Client.h"

int main(int argc, char** argv){
    // 47.243.244.116:8888
    Client* client = new Client(new Socket(argv[1], atoi(argv[2])), 111);
    client->connect();
    char* id;
    cout << "Type your account id in 3 digit: \n";
    cin.getline(id, 4);
    client->setAccountId(atoi(id));
    write(client->getSocket()->getSockfd(), id, 4);
    cout << "-----list: list online user ids-----\n";
    cout << "-----chat: send message-----\n";
    cout << "-----recv: receive message-----\n";
    cout << "-----exit: exit program-----\n";
    cout << "-----help: show help-----\n";
    while(true){
        char* cmd;
        cin.getline(cmd, 10);
        if (strcmp(cmd, "exit") == 0){
            break;
        }
        else if (strcmp(cmd, "help") == 0){
            cout << "-----list: list online user ids-----\n";
            cout << "-----chat: send message-----\n";
            cout << "-----recv: receive message-----\n";
            cout << "-----exit: exit program-----\n";
            cout << "-----help: show help-----\n";
        }
        else if(strcmp(cmd, "list") == 0){
            cout << "Online user ids: \n";
        }
        else if(strcmp(cmd, "chat") == 0){
            cout << "Choose target id to send message: \n";
            cin.getline(id, 4);
            client->sendMessage(atoi(id));
        }
        else if(strcmp(cmd, "recv") == 0){
            client->recvMessage();
        }
        else{
            cout << "Invalid command! Type 'help' for more information\n";
        }
        
    }
    
    delete client;
}