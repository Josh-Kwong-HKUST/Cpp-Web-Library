#include "Channel.h"

Channel::Channel(Epoll* ep, int fd): ep(ep), fd(fd), listenEvents(0), happenEvents(0), inEpoll(false){}

void Channel::enableReading(){
    listenEvents = EPOLLIN | EPOLLET; // EPOLLET: Edge Triggered
    ep->updateChannel(this);
}

int Channel::getFd(){
    return fd;
}

uint32_t Channel::getListenEvents(){
    return listenEvents;
}

uint32_t Channel::getHappenEvents(){
    return happenEvents;
}

bool Channel::getInEpoll(){
    return inEpoll;
}

void Channel::setInEpoll(){
    inEpoll = true;
}

void Channel::setHappenEvents(uint32_t ev){
    this->happenEvents = ev;
}
