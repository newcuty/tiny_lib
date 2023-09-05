
#ifndef _TINY_LIB_NET_SOCKET_H_
#define _TINY_LIB_NET_SOCKET_H_

#include <sys/types.h>          /* See NOTES */
#include <sys/socket.h>
#include <unistd.h>
#include <fcntl.h>

#include <unistd.h>
#include <cstring>
#include <iostream>

#include "inet_address.hpp"


namespace tiny_lib::net{

class Socket{

public:
    //initialize a socket, should support ipv4 and ipv6(update later), also support block and non-block
    explicit Socket(/*sa_family_t& family,*/  bool isBlocking = false);
    explicit Socket(socket_fd_t& fd);
    virtual ~Socket();

    //bind a the socket to address
    void Bind(tiny_lib::InetAddress& inet_address);

    //listen a socket 
    void Listen();

    //Accept the client to connect
    tiny_lib::socket_fd_t Accept(tiny_lib::InetAddress& inet_address);

    //connect to the server
    void Connect(tiny_lib::InetAddress& inet_address);

    //set non-blocking socket
    void SetNonBlocking();

    void SetFdOvertime(struct timeval& tv);

    //close the socket fd;
    void Close();

    //get the socket fd, cant modify by outside
    const tiny_lib::socket_fd_t& GetFd(){
        return socketfd_;
    }

protected:
    tiny_lib::socket_fd_t socketfd_;    //socket fd


};

}

#endif
