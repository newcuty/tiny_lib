#include "socket.h"

namespace tiny_lib::net{

Socket::Socket(/*sa_family_t& family,*/ bool isBlocking){

    //create a block socket
    if (isBlocking == true){
        socketfd_ = socket(AF_INET, SOCK_STREAM | SOCK_CLOEXEC, IPPROTO_TCP);
    }else{  //create a block socket
        socketfd_ = socket(AF_INET, SOCK_STREAM | SOCK_NONBLOCK | SOCK_CLOEXEC, IPPROTO_TCP);
    }

    if(-1 == socketfd_){
        std::cout << "create socket error";
    }

    std::cout << "init socket success\n";
}

Socket::Socket(socket_fd_t& fd){

    if(-1 != fd){
        std::cout << "socket create error\n";
        socketfd_ = -1;

        return;
    }

    socketfd_ = fd;
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
        perror("bind address error\n");
        return;
    }

    std::cout << "bind socket success\n";
}

void Socket::SetNonBlocking(){

    //set the socket fd as non-blocking fd
    int fcnret = fcntl(socketfd_, F_SETFL, fcntl(socketfd_, F_GETFL) | O_NONBLOCK);
    if(-1 == fcnret){

        std::cout << "fcntl set non-blocking fd error\n";
    }
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
        perror("connect error");
        exit(0);
    }

    std::cout << "connect success\n";

    return;
}

void Socket::SetFdOvertime(struct timeval& tv){

    int setopt_ret = setsockopt(socketfd_, SOL_SOCKET, SO_SNDTIMEO, &tv, sizeof(tv));
    if(-1 == setopt_ret){

        perror("setsockopt error");
        return;
    }

    std::cout << "setsockopt success\n";
}


void Socket::Close(){
    close(socketfd_);
}

}
