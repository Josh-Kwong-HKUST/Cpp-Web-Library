#pragma once


class Epoll;
class Channel;
class Eventloop{
    private:
        Epoll* epoll;
        bool quit;
    public:
        Eventloop();
        ~Eventloop();

        void loop();
        void updateChannel(Channel* channel);
};