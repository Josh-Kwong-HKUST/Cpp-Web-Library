#include "../include/Eventloop.h"
#include "../include/Epoll.h"
#include "../include/Channel.h"

Eventloop::Eventloop(){
    epoll = new Epoll();
    quit = false;
}

Eventloop::~Eventloop(){
    delete epoll;
}

void Eventloop::loop(){
    while(!quit){
        std::vector<Channel*> channels = epoll->poll();
        for(auto channel : channels){
            channel->handleEvent();
        }
    }
}

void Eventloop::updateChannel(Channel* channel){
    epoll->updateChannel(channel);
}