#ifndef _EPOLL_H_
#define _EPOLL_H_

//this is a class for epoll
#include <sys/epoll.h>

#include <iostream>
#include <vector>

#include "tiny_types.h"

namespace tiny_lib::base{

class Epoll{
public:
    //constrcut a epoll instance
    explicit Epoll();  
    void AddFd(socket_fd_t& server_fd, EPOLL_EVENTS& event);
    //void DeleteFd(socket_fd_t& server_fd, EPOLL_EVENTS& event);


    //return teh epoll fd
    const socket_fd_t& GetEpollFd(){
        return epollfd_;
    } 


protected:
    socket_fd_t epollfd_;
    std::vector<struct epoll_event> epoll_events;



};
    

}

#endif