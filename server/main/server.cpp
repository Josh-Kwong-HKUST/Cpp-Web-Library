#include "../include/Server.h"
#include "../include/Message.h"

// void forwardMessage(int cli_fd, char buffer[BUFFER_SIZE + 7]){
//     Message* msg = new Message(buffer);
//     int toId = msg->getToId();
//     /*
//         999 means broadcast
//         server broadcast the message to all clients
//     */
//     if (toId == 999){
//         for (auto client : mapIdToClient){
//             int targetFd = client.second->getSocket()->getSockfd();
//             if (targetFd == cli_fd) continue;
//             printf("Broadcasting message from %d to %d\n", msg->getFromId(), client.first);
//             printf("Content: %s\n", msg->getContent());
//             if(send(targetFd, buffer, BUFFER_SIZE + 7, 0) == -1)
//                 printf("=====Error: Failed to send message to client %d! Errno: %s=====\n", targetFd, strerror(errno));
//         }
//     }
//     else if (toId == 998){   // 998 means this is a request to server, server needs to respond the online list
//         string onlineList = "Current online: ";
//         for (auto client : mapIdToClient){
//             onlineList += to_string(client.first) + " ";
//         }
//         onlineList += "\0";
//         cout << onlineList.c_str() << "\n";
//         Client* fromClient = mapIdToClient[msg->getFromId()];
//         Message* msg_ = new Message(998, fromClient->getAccountId());
//         char* content = msg_->getContent();
//         memcpy(content, onlineList.c_str(), onlineList.length());
//         char buffer[BUFFER_SIZE + 7];
//         msg_->serializeMessage(buffer);
//         send(fromClient->getSocket()->getSockfd(), buffer, BUFFER_SIZE + 7, 0);
//         delete msg_;
//     }
//     else if(toId >= 100 && toId < 998){ //private chat
//         if (mapIdToClient.find(toId) == mapIdToClient.end()){
//             printf("-----System message: Forwarding target id = %d not found!-----\n", toId);
//             return;
//         }
//         Client* toClient = mapIdToClient[toId];
//         int targetFd = toClient->getSocket()->getSockfd();
//         send(targetFd, buffer, BUFFER_SIZE + 7, 0);
//     }
//     delete msg;
// }

int main(int argc, char** argv){
    Eventloop* loop = new Eventloop();
    Server* server = new Server(atoi(argv[1]), loop);
    server->onConnect([](Connection* conn){     // customize service logic
        conn->read();
        const char* str = conn->getReadBuffer()->toStr();
        printf("Received message: %s\n", str);
        conn->setWriteBuffer(str);
        conn->write();
    });
    loop->loop();
    delete server;
    delete loop;
    return 0;
}