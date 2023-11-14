#pragma once
#include <string>
#include <mysql/mysql.h>

using string = std::string;
class MysqlConnection {

enum MysqlConnectionState{
    AVAILABLE,
    BUSY
};

public:
    MysqlConnection(string host, string user, string passwd, string dbName, unsigned int port);
    ~MysqlConnection();
    bool connect();
    bool query(string sql);
    bool next();
    bool update(string sql);
    void setState(MysqlConnectionState state);
private:
    string host;
    string user;
    string passwd;
    string dbName;
    unsigned int port;
    MysqlConnectionState state; 
    MYSQL* mysql;
    MYSQL_RES* result;
    MYSQL_ROW row;
    void freeResult();
};