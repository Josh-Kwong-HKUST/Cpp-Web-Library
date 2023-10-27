#include "Epoll.h"
#include <string.h>
#include <sys/epoll.h>
#include <iostream>

void Epoll::addSocket(Socket* socket){
    socket->setNonBlocking();
    int fd = socket->getSockfd();
    epoll_event event;
    bzero(&event, sizeof(event));  
    event.data.fd = fd;
    event.events = EPOLLIN;
    if(epoll_ctl(epollFd, EPOLL_CTL_ADD, fd, &event) == -1){
        std::cerr << "=====Error: epoll failed to add file descriptor, Errno: " << strerror(errno) << "=====\n";
        exit(-1);
    }
}

std::vector<epoll_event> Epoll::poll(int timeout){
    std::vector<epoll_event> activeEvents;
    int numFds = epoll_wait(epollFd, events, MAXEVENTS, timeout);
    if (numFds == -1){
        std::cerr << "=====Error: epoll failed to wait, Errno: " << strerror(errno) << "=====\n";
        exit(-1);
    }
    for (int i = 0; i < numFds; i++){
        activeEvents.push_back(events[i]);
    }
    return activeEvents;
}
