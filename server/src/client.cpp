#include "../include/ClientSocket.h"

int main(){
    ClientSocket client("127.0.0.1", 8888);
    client.connectToServer();
}