#pragma once
#include <string>
#include <mysql/mysql.h>
#include <chrono>
#include <unistd.h>
using string = std::string;
class MysqlConnection {

public:
    MysqlConnection();
    ~MysqlConnection();
    bool connect(string host, string user, string passwd, string dbName, unsigned int port);
    bool query(string sql);
    bool next();
    bool update(string sql);
    void refreshAvailableTime();
    std::chrono::steady_clock::time_point getAvailableTime() const;
private:
    MYSQL* mysql;
    MYSQL_RES* result;
    MYSQL_ROW row;
    std::chrono::steady_clock::time_point availableTime;
    void freeResult();
};