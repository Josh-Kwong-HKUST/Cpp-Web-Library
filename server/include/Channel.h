#pragma once
#include <sys/epoll.h>
#include <functional>

class Eventloop;
class Channel
{
    private:
        Eventloop *loop;  // the event loop that this channel belongs to
        int fd;
        uint32_t listenEvents;    // events that this channel listens to
        uint32_t happenEvents;   // the event is happening when Epoll return this channel
        bool inEpoll;    // whether this channel is in Epoll
        std::function<void()> callback;    // the callback function that will be called when the event happens
    public:
        Channel(Eventloop* _loop, int _fd);

        void enableReading();
        int getFd();
        uint32_t getListenEvents();
        uint32_t getHappenEvents();
        bool getInEpoll();
        void setInEpoll();
        void setHappenEvents(uint32_t);
        void handleEvent();
        void setCallback(std::function<void()> cb);
};