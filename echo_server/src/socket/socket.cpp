#include "socket.h"

namespace tiny_lib::net{

Socket::Socket(/*sa_family_t& family,*/ bool isBlocking){

    //create a block socket
    if (isBlocking == false){
        socketfd_ = socket(AF_INET, SOCK_STREAM | SOCK_CLOEXEC, IPPROTO_TCP);
    }else{  //create a block socket
        socketfd_ = socket(AF_INET, SOCK_STREAM | SOCK_NONBLOCK | SOCK_CLOEXEC, IPPROTO_TCP);
    }

    if(-1 == socketfd_){
        std::cout << "create socket error";
    }

    std::cout << "init socket success\n";
}
Socket::~Socket(){

    if (-1 != socketfd_ ){
        close(socketfd_);
    }

    std::cout << "close socket success\n";
}


void Socket::Bind(tiny_lib::InetAddress& inet_address){

    int bindret = bind(socketfd_, inet_address.GetSockAddrType(), inet_address.GetAddrLen());

    if(-1 == bindret){
        std::cout << "bind address error";
    }

    std::cout << "bind socket success\n";
}


void Socket::Listen(){

    int listenret = listen(socketfd_, 5);

    if(-1 == listenret){
        std::cout << "listen error";
    }

    std::cout << "listen socket success\n";
}


tiny_lib::socket_fd_t Socket::Accept(tiny_lib::InetAddress& inet_address){

    //accept will return a socket fd for client
    tiny_lib::socket_fd_t client_fd = accept(socketfd_, inet_address.GetSockAddrType(), &inet_address.GetAddrLen());

    if(-1 == client_fd){
        std::cout << "accept error";
        return -1;
    }


    return client_fd;
}


void Socket::Connect(tiny_lib::InetAddress& inet_address){

    int connect_ret = connect(socketfd_, inet_address.GetSockAddrType(), inet_address.GetAddrLen());
    if (-1 == connect_ret){

        std::cout << "connect error \n";
        return;
    }

    std::cout << "connect success\n";

    return;
}


}
