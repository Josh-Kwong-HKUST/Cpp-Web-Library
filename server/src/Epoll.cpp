#include "../include/Epoll.h"
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

std::vector<Channel*> Epoll::poll(int timeout){
    std::vector<Channel*> activeChannels;
    int numFds = epoll_wait(epollFd, events, MAXEVENTS, timeout);
    if (numFds == -1){
        std::cerr << "=====Error: epoll failed to wait, Errno: " << strerror(errno) << "=====\n";
        exit(-1);
    }
    for (int i = 0; i < numFds; i++){
        Channel* ch = (Channel*)events[i].data.ptr;
        ch->setHappenEvents(events[i].events);
        activeChannels.push_back(ch);
    }
    return activeChannels;
}

void Epoll::updateChannel(Channel* channel){
    int fd = channel->getFd();
    epoll_event ev;
    bzero(&ev, sizeof(ev));
    ev.data.ptr = channel;
    ev.events = channel->getListenEvents();
    if(!channel->getInEpoll()){
        if(epoll_ctl(epollFd, EPOLL_CTL_ADD, fd, &ev) == -1){
            std::cerr << "=====Error: epoll failed to add channel, Errno: " << strerror(errno) << "=====\n";          
        }
        channel->setInEpoll();
    }
    else{
        if(epoll_ctl(epollFd, EPOLL_CTL_MOD, fd, &ev) == -1){
            std::cerr << "=====Error: epoll failed to modify channel, Errno: " << strerror(errno) << "=====\n";
        }
    }
}
