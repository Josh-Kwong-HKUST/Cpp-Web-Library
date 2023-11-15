# pragma once

#include "MysqlConnection.h"

#include <memory>
#include <queue>
#include <mutex>
#include <condition_variable>
#include <string>
#include <thread>

using string = std::string;

#define MAX_IDLE_TIME 600000        // 10 minutes
#define MIN_CONNECTION_NUM 5
class MysqlConnectionPool {

private:
    std::queue<MysqlConnection*> connectionQueue;
    std::mutex queue_mutex;
    std::condition_variable condition;
    string host;
    string user;
    string passwd;
    string dbName;
    unsigned int port;
    static MysqlConnectionPool* poolInstance;
    MysqlConnectionPool(string host, string user, string passwd, string dbName, unsigned int port);
public:
    static MysqlConnectionPool  *getInstance();    // static function to get the singleton object
    std::shared_ptr<MysqlConnection>   getConnection();

    // ban copy constructor and assignment operator
    MysqlConnectionPool(const MysqlConnectionPool &obj) = delete;
    MysqlConnectionPool& operator=(const MysqlConnectionPool& obj) = delete;
    ~MysqlConnectionPool();
};