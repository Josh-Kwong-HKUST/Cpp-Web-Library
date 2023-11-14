#include "../include/MysqlConnectionPool.h"

MysqlConnectionPool::MysqlConnectionPool(string _host, string _user, string _passwd, string _dbName, unsigned int _port): host(_host), user(_user), passwd(_passwd), dbName(_dbName), port(_port){
    std::thread producer([this]()->void{
        while(true){
            std::unique_lock locker(queue_mutex);
            while (connectionQueue.size() <= std::thread::hardware_concurrency()){
                condition.wait(locker);
            }
            MysqlConnection* conn = new MysqlConnection();
            if (conn->connect(host, user, passwd, dbName, port)){
                conn->refreshAvailableTime();
                connectionQueue.push(conn);
                printf("New MysqlConnection created! Current connection queue length: %lu\n", connectionQueue.size());
            }
            condition.notify_all();
        }
    });
    producer.detach();

    std::thread recycler([this]()->void{
        while(true){
            std::this_thread::sleep_for(std::chrono::milliseconds(500));
            std::unique_lock<std::mutex> locker(queue_mutex);
            // keep the minimum number of connections
            while(connectionQueue.size() > 5){
                MysqlConnection *recyConn = connectionQueue.front();
                // recycly when idle timeout
                if(std::chrono::steady_clock::now() - recyConn->getAvailableTime() >= std::chrono::milliseconds(14400000)){
                    connectionQueue.pop();
                    delete recyConn;
                    printf("Recycle a MysqlConnection! Current connection queue length: %lu\n", connectionQueue.size());
                } 
                else    break;
            }
        }
    });
    recycler.detach();
}

MysqlConnectionPool::~MysqlConnectionPool(){
    while (!connectionQueue.empty()){
        connectionQueue.pop();
    }
}

MysqlConnectionPool* MysqlConnectionPool::getInstance()
{
    if (poolInstance == nullptr)     poolInstance = new MysqlConnectionPool("localhost", "root", "123456", "test", 0);
    return poolInstance;
}

std::shared_ptr<MysqlConnection> MysqlConnectionPool::getConnection(){
    std::unique_lock<std::mutex> locker(queue_mutex);
    while(connectionQueue.empty()){ // wait for available connection
        if(std::cv_status::timeout == condition.wait_for(locker, std::chrono::milliseconds(500)))
        {
            if(connectionQueue.empty())
            {
                continue;
            }
        }
    }
    // the second parameter is a self-defined deleter for this shared_ptr
    // the deleter is used to push the connection back to the queue when the shared_ptr is destroyed
    auto conn = std::shared_ptr<MysqlConnection>(connectionQueue.front(), [this](MysqlConnection* conn){
        std::unique_lock<std::mutex> locker(queue_mutex);
        conn->refreshAvailableTime();
        connectionQueue.push(conn);
    });
    connectionQueue.pop();
    condition.notify_all();
    return conn;
}