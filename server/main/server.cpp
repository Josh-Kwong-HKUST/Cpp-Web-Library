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