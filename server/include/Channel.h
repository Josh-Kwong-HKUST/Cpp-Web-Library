#pragma once
#include <sys/epoll.h>
#include "Epoll.h"

class Epoll;
class Channel
{
    private:
        Epoll *ep;  // the Epoll that this channel belongs to
        int fd;
        uint32_t listenEvents;    // events that this channel listens to
        uint32_t happenEvents;   // the event is happening when Epoll return this channel
        bool inEpoll;    // whether this channel is in Epoll
    public:
        Channel(Epoll *_ep, int _fd);

        void enableReading();
        int getFd();
        uint32_t getListenEvents();
        uint32_t getHappenEvents();
        bool getInEpoll();
        void setInEpoll();
        void setHappenEvents(uint32_t);
};