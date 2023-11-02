#pragma once
#include "Channel.h"
#include "Eventloop.h"
#include "Socket.h"
#include "Macros.h"
#include "Buffer.h"

class Connection{
public:
    enum State {
    Invalid = 1,
    Handshaking,
    Connected,
    Closed,
    Failed,
  };
private:
    State state{Invalid};
    Eventloop* loop;
    Socket* sock;
    Channel* channel;
    Buffer* readBuffer;
    Buffer* writeBuffer;
    std::function<void(Connection*)> onConnectCallback;
    std::function<void(Socket*)> onDeleteConnectionCallback;
public:
    Connection(Eventloop* _loop, Socket* _sock);
    ~Connection();
    void setOnDeleteConnectionCallback(std::function<void(Socket*)> cb);
    void setOnConnectCallback(std::function<void(Connection*)> cb);
    void read();
    void write();
    void readNonBlocking();
    void readBlocking();
    void writeNonBlocking();
    void writeBlocking();
    State getState() const;
    Socket* getSocket() const;
    Buffer* getReadBuffer() const;
    Buffer* getWriteBuffer() const;
    void setWriteBuffer(const char*);
    void setWriteBufferGetline();
};