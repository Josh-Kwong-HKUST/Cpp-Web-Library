#include "../include/Connection.h"

Connection::Connection(Eventloop* _loop, Socket* _sock): loop(_loop), 
                                                         sock(_sock),
                                                         readBuffer(nullptr),
                                                         writeBuffer(nullptr),
                                                         onConnectCallback(nullptr),
                                                         onDeleteConnectionCallback(nullptr),
                                                         mutexLock()
{
    readBuffer = new Buffer();
    writeBuffer = new Buffer();
    setState(State::Connected);
    if (!loop){
      channel = nullptr;
      return;
    }
    channel = new Channel(loop, sock->getSockfd());
    channel->enableRead();
    channel->enableET();
    channel->setInEpoll();
}

Connection::~Connection(){
    delete channel;
    delete sock;
}

void Connection::setOnConnectCallback(std::function<void(Connection*)> cb){
    onConnectCallback = cb;
    this->channel->setCallback([this](){
        onConnectCallback(this);    // channel calls the callback function with this connection as the argument
    });
}

void Connection::setOnDeleteConnectionCallback(std::function<void(Socket*)> cb){
    onDeleteConnectionCallback = cb;
}

Connection::State Connection::getState() const{
    return state;
}

void Connection::read() {
  if(!(state == State::Logined || state == State::Connected)){
      printf("Connection READ error: connection state is disconnected! State: %d\n", state);
      return;
    }
  readBuffer->clear();
  if (sock->isNonBlocking()) {
    readNonBlocking();
  } else {
    readBlocking();
  }
}

void Connection::write(){
    if(!(state == State::Logined || state == State::Connected)){
      printf("Connection WRITE error: connection state is disconnected! State: %d\n", state);
      return;
    }
    if (sock->isNonBlocking()){
        writeNonBlocking();
    } else {
        writeBlocking();
    }
    writeBuffer->clear();
}

void Connection::readNonBlocking() {
  int sockfd = sock->getSockfd();
  char buf[1024];
  while (true) {
    memset(buf, 0, sizeof(buf));
    ssize_t bytes_read = recv(sockfd, buf, sizeof(buf), 0);
    if (bytes_read > 0) {
      readBuffer->append(buf, bytes_read);
    } else if (bytes_read == -1 && errno == EINTR) {
      printf("continue reading\n");
      continue;
    } else if (bytes_read == -1 &&
               ((errno == EAGAIN) || (errno == EWOULDBLOCK))) {  // finish reading
      break;
    } else if (bytes_read == 0) {  // EOF，client disconnected
      printf("read EOF, client fd %d disconnected\n", sockfd);
      setState(State::Closed);
      break;
    } else {
      printf("Other error on client fd %d\n", sockfd);
      setState(State::Closed);
      break;
    }
  }
}
void Connection::writeNonBlocking() {
  int sockfd = sock->getSockfd();
  char buf[writeBuffer->size()];
  memcpy(buf, writeBuffer->toStr(), writeBuffer->size());
  int data_size = writeBuffer->size();
  int data_left = data_size;
  while (data_left > 0) {
    ssize_t bytes_write = send(sockfd, buf + data_size - data_left, data_left, 0);
    if (bytes_write == -1 && errno == EINTR) {
      printf("continue writing\n");
      continue;
    }
    if (bytes_write == -1 && errno == EAGAIN) {
      break;
    }
    if (bytes_write == -1) {
      printf("Other error on client fd %d\n", sockfd);
      setState(State::Closed);
      break;
    }
    data_left -= bytes_write;
  }
}

/**
 * @brief Never used by server, only for client
 *
 */
void Connection::readBlocking() {
  int sockfd = sock->getSockfd();
  unsigned int rcv_size = 0;
  socklen_t len = sizeof(rcv_size);
  getsockopt(sockfd, SOL_SOCKET, SO_RCVBUF, &rcv_size, &len);
  char buf[rcv_size];
  ssize_t bytes_read = recv(sockfd, buf, sizeof(buf), 0);
  if (bytes_read > 0) {
    readBuffer->append(buf, bytes_read);
  } else if (bytes_read == 0) {
    printf("read EOF, blocking client fd %d disconnected\n", sockfd);
    setState(State::Closed);
  } else if (bytes_read == -1) {
    printf("Other error on blocking client fd %d\n", sockfd);
    setState(State::Closed);
  }
}

/**
 * @brief Never used by server, only for client
 *
 */
void Connection::writeBlocking() {
  // not handle buffer overflow
  int sockfd = sock->getSockfd();
  ssize_t bytes_write = send(sockfd, writeBuffer->toStr(), writeBuffer->size(), 0);
  if (bytes_write == -1) {
    printf("Other error on blocking client fd %d\n", sockfd);
    setState(State::Closed);
  }
}

Socket* Connection::getSocket() const{
    return sock;
}

Buffer* Connection::getReadBuffer() const{
    return readBuffer;
}

Buffer* Connection::getWriteBuffer() const{
    return writeBuffer;
}

void Connection::setWriteBuffer(const char* _buf){
    writeBuffer->setBuf(_buf);
}

void Connection::setWriteBufferGetline(){
    writeBuffer->getline();
}

void Connection::setState(State _state){
    mutexLock.lock();
    state = _state;
    mutexLock.unlock();
}

void Connection::Close() const{
    onDeleteConnectionCallback(sock);
}