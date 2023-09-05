#ifndef _EPOLL_H_
#define _EPOLL_H_

//this is a class for epoll
#include <sys/epoll.h>

#include <iostream>
#include <vector>
#include <mutex>

#include "tiny_types.h"

namespace tiny_lib::net{

typedef struct epoll_event EpollEvent;

class Epoll{
public:
    //constrcut a epoll instance
    explicit Epoll(); 

    void AddFd(const socket_fd_t& server_fd, EPOLL_EVENTS& event);
    //void DeleteFd(socket_fd_t& server_fd, EPOLL_EVENTS& event);

    //wrpper of epoll_wait()
    std::vector<EpollEvent>& Poll(int32_t timout = -1);

    //return teh epoll fd
    const socket_fd_t& GetEpollFd(){
        return epollfd_;
    } 


protected:
    socket_fd_t epollfd_;
    std::vector<EpollEvent> epoll_events_;
    std::vector<EpollEvent> active_events_;

    std::mutex poll_mutex_;
};
    

}

#endif