#include "Channel.h"
#include "Eventloop.h"

Channel::Channel(Eventloop *_loop, int _fd): loop(_loop), fd(_fd), listenEvents(0), happenEvents(0), inEpoll(false){}

void Channel::enableReading(){
    listenEvents = EPOLLIN | EPOLLET; // EPOLLET: Edge Triggered
    loop->updateChannel(this);
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

void Channel::handleEvent(){
    callback();
}

void Channel::setCallback(std::function<void()> cb){
    callback = cb;
}
