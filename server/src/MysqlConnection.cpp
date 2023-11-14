#include "../include/MysqlConnection.h"
#include <mysql/mysql.h>

MysqlConnection::MysqlConnection(): result(nullptr), row(nullptr){
    mysql = mysql_init(nullptr);
    mysql_set_character_set(mysql, "uft-8");
}

MysqlConnection::~MysqlConnection(){
    mysql_close(mysql);
}

bool MysqlConnection::connect(string host, string user, string passwd, string dbName, unsigned int port){
    if (mysql_real_connect(mysql, host.c_str(), user.c_str(), passwd.c_str(), dbName.c_str(), port, nullptr, 0)){
        return true;
    }
    return false;
}

void MysqlConnection::freeResult()
{
    if(result)
    {
        mysql_free_result(result);
        result = nullptr;
    }
}

bool MysqlConnection::update(string sql)
{
    if(mysql_query(mysql,sql.c_str()))
    {
        return false;
    }
 
    return true;
}
 
bool MysqlConnection::query(string sql)
{
    freeResult();
    if(mysql_query(mysql,sql.c_str()))
    {
        return false;
    }
    result = mysql_store_result(mysql);
 
    return true;
}

bool MysqlConnection::next()
{
    if(!result)
    {
        return false;
    }
    row = mysql_fetch_row(result);
    if(!row)
    {
        return false;
    }
    return true;
}

void MysqlConnection::refreshAvailableTime(){
    this->availableTime = std::chrono::steady_clock::now();
}

std::chrono::steady_clock::time_point MysqlConnection::getAvailableTime() const{
    return this->availableTime;
}