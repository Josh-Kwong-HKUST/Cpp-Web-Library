# pragma once

#include "MysqlConnection.h"

#include <memory>
#include <queue>

class MysqlConnectionPool {

private:
    std::queue<std::unique_ptr<MysqlConnection>> connectionQueue;
    int poolSize;

public:

};