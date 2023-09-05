#include "epoll.h"

namespace tiny_lib::net{

Epoll::Epoll(){

    epollfd_ = epoll_create1(0);
    if (-1 == epollfd_){
        std::cout << "creat epoll fd failed\n";
    }

    //allocate the size of epoll events
    epoll_events_.reserve(1024); 
}

void Epoll::AddFd(const socket_fd_t& server_fd, EPOLL_EVENTS& event){

    EpollEvent ev;

    ev.events = event;
    ev.data.fd = server_fd;

    if (-1 == epoll_ctl(epollfd_, EPOLL_CTL_ADD, server_fd, &ev)){

        std::cout << "epoll_ctl server_fd:" << server_fd << " failed\n";         
    }
}

std::vector<EpollEvent>& Epoll::Poll(int32_t timout){

    //add a mutex,avoid data raceing after call the poll
    std::lock_guard<std::mutex> lockGuard(poll_mutex_);
    
    //before call epoll wait, the active events vector should be cleared
    active_events_.clear();

    //call the epoll_wait, wait for the active events
    int32_t ready_fd = epoll_wait(epollfd_, epoll_events_.data(), 1024, timout);

    //handle the 
    if(-1 == ready_fd){

        std::cout << "epoll_wait error occurs\n";
    }

    //add the epoll events into active events array and return to the caller
    for(int i = 0; i < ready_fd; i++){

        active_events_.push_back(epoll_events_[i]);
    }

    return active_events_;
}



}