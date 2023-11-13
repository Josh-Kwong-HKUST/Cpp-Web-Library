#include "../include/Server.h"
#include "../include/Message.h"
#include "../include/utils.hpp"
#include <mysql/mysql.h>

#define MYSQL_HOST "localhost"   //47.243.244.116
#define MYSQL_USER "root"
#define MYSQL_PASS "123456"
#define MYSQL_DB "chatroom"
#define MYSQL_TABLE "userData"
#define NAME_FIELD "userName"
#define PASS_FIELD "userPasswd"
#define FIELD_TUPLE "(userName, userPasswd)"

const char* loginOrRegisterRequestHandler(const char* request){
    auto tokens = splitString(request, ' ');
    if (tokens.size() != 3){
        return "Failed, invalid request format! Please use /login or /register!";
    }
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
    auto* loop = new Eventloop();
    auto* server = new Server(atoi(argv[1]), loop);
    server->onConnect([&server](Connection* conn){     // customize service logic
        while(true){
            if(conn->getState() != Connection::State::Logined){
                conn->read();
                if (conn->getReadBuffer()->size() == 0) continue;
                const char* request = conn->getReadBuffer()->toStr();
                const char* response = loginOrRegisterRequestHandler(request);
                conn->setWriteBuffer(response);
                conn->write();
                if (strcmp(response, "OK") == 0){
                    printf("Good response\n");
                    conn->setState(Connection::State::Logined);
                }
                else{
                    printf("Notify client that request not correctly handled\n");
                }
            }
            // service logic
            else{
                conn->read();
                if (conn->getState() == Connection::State::Closed){
                    conn->Close();
                    break;
                }
                server->broadcast(conn->getReadBuffer()->toStr(), conn->getSocket()->getSockfd());
            }
        }
    });
    loop->loop();
    delete server;
    delete loop;
    return 0;
}