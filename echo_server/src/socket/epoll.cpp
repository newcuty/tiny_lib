#include "epoll.h"

namespace tiny_lib::base{

Epoll::Epoll(){

    epollfd_ = epoll_create1(0);
    if (-1 == epollfd_){
        std::cout << "creat epoll fd failed\n";
    }

}

void Epoll::AddFd(socket_fd_t& server_fd, EPOLL_EVENTS& event){

    epoll_ev_.events = event;
    epoll_ev_.data.fd = server_fd;

    if (-1 == epoll_ctl(epollfd_, EPOLL_CTL_ADD, server_fd, &epoll_ev_)){

        std::cout << "epoll_ctl server_fd:" << server_fd << " failed\n";         
    }

}



}