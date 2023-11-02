#include "../include/Server.h"
#include "../include/Message.h"
#include "../include/utils.hpp"
#include <mysql/mysql.h>

#define MYSQL_HOST "47.243.244.116"
#define MYSQL_USER "root"
#define MYSQL_PASS "123456"
#define MYSQL_DB "chatroom"
#define MYSQL_TABLE "userData"
#define NAME_FIELD "userName"
#define PASS_FIELD "userPasswd"
#define FIELD_TUPLE "(userName, userPasswd)"

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
const char* loginOrRegisterRequestHandler(const char* request){
    auto tokens = splitString(request, ' ');
    auto requestType = tokens[0];
    auto userName = tokens[1];
    auto userPasswd = tokens[2];
    if (requestType == "/login"){
        MYSQL* mysql = mysql_init(nullptr);
        printf("Connecting to mysql...\n");
        mysql_real_connect(mysql, MYSQL_HOST, MYSQL_USER, MYSQL_PASS, MYSQL_DB, 0, nullptr, 0);
        printf("Connected to mysql!\n");
        string query = "SELECT * FROM " + string(MYSQL_TABLE) + " WHERE " + string(NAME_FIELD) + " = '" + userName + "' AND " + string(PASS_FIELD) + " = '" + userPasswd + "'";
        mysql_query(mysql, query.c_str());
        MYSQL_RES* result = mysql_store_result(mysql);
        if (mysql_num_rows(result) == 0){
            return "Failed, user name or password incorrect!";
        }
        else{
            return "OK";
        }
    }
    else if (requestType == "/register"){
        MYSQL* mysql = mysql_init(nullptr);
        mysql_real_connect(mysql, MYSQL_HOST, MYSQL_USER, MYSQL_PASS, MYSQL_DB, 0, nullptr, 0);
        string query = "SELECT * FROM " + string(MYSQL_TABLE) + " WHERE " + string(NAME_FIELD) + " = '" + userName + "'";
        mysql_query(mysql, query.c_str());
        MYSQL_RES* result = mysql_store_result(mysql);
        if (mysql_num_rows(result) != 0){
            return "Failed, user name already exists!";
        }
        else{
            query = "INSERT INTO " + string(MYSQL_TABLE) + FIELD_TUPLE + " VALUES ('" + userName + "', '" + userPasswd + "')";
            mysql_query(mysql, query.c_str());
            return "OK";
        }
    }
    else{
        return "Failed, invalid request type! Please use /login or /register!";
    }
}
int main(int argc, char** argv){
    Eventloop* loop = new Eventloop();
    Server* server = new Server(atoi(argv[1]), loop);
    server->onConnect([](Connection* conn){     // customize service logic
        if(conn->getState() != Connection::State::Logined){
            while(true){
                conn->read();
                const char* request = conn->getReadBuffer()->toStr();
                printf("Received request: %s\n", request);
                const char* response = loginOrRegisterRequestHandler(request);
                conn->setWriteBuffer(response);
                conn->write();
                if (strcmp(response, "OK") == 0) break;
            }
            conn->setState(Connection::State::Logined);
        }
        else{
            // echo
            conn->read();
            conn->setWriteBuffer(conn->getReadBuffer()->toStr());
            conn->write();
        }
    });
    loop->loop();
    delete server;
    delete loop;
    return 0;
}