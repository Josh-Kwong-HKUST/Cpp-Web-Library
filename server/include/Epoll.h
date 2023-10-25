#pragma once
#include <sys/epoll.h>
#include <vector>
#include <unistd.h>
#include "Socket.h"
#include <errno.h>

#define MAXEVENTS 1024

class Epoll{
    /*
        event value:
        EPOLLIN: can read from socket. remote close connection also triggers this event since FIN package is readable
        EPOLLOUT: can write to socket.
        EPOLLET: edge trigger
        EPOLLPRI: urgent data to be read
        EPOLLERR: connection error occurs
        EPOLLHUP: hang up
        EPOLLRDHUP: remote close connection
        EPOLLONESHOT: one handle only to this event, need to add to epoll again next time
    */
    private:
        int epollFd;
        epoll_event* events;
    public:
        Epoll(){
            epollFd = epoll_create(MAXEVENTS);
            if(epollFd == -1){
                std::cerr << "=====Error: epoll failed to create, Errno: " << strerror(errno) << "=====\n";
                exit(-1);
            }
            events = new epoll_event[MAXEVENTS];
        };
        ~Epoll(){
            if (epollFd != -1){
                close(epollFd);
                epollFd = -1;
            }
            delete[] events;
        }
        int getEpollFd(){
            return epollFd;
        }
        void Init(Socket* socket);
        void addSocket(Socket* socket);
        // void modifyFd(int fd);
        // void deleteFd(int fd);
        // void wait();
        std::vector<epoll_event> poll(int timeout = -1);
};