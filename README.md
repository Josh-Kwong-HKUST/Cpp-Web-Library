# C++ Web-Server Library
A comprehensive and generic C++ library for building web servers.

## Compile
```bash
./build.sh
```

## Sample usage
### Server
```cpp
int main(int argc, char** argv){
    auto* loop = new Eventloop();
    auto* server = new Server(atoi(argv[1]), loop);
    auto* mysqlPool = MysqlConnectionPool::getInstance();
    server->onConnect([&server, &mysqlPool](Connection* conn){
        // Customize service logic
    });
    loop->loop();
    delete server;
    delete loop;
    delete mysqlPool;
    return 0;
}
```
```bash
./server 8888
// 8888 is the port used by server to listen
```
