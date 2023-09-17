#include <thread>

#include "socket.h"
#include "inet_address.hpp"


const int buf_size = 1024;

int main(int argc, char** argv){

    tiny_lib::net::Socket client_socket(true);

    //set overtime,because the socket is nonblocking
    struct timeval tv;
    tv.tv_sec = 5;
    tv.tv_usec = 0;
    client_socket.SetFdOvertime(tv);

    std::string ipaddr("127.0.0.1"); 
    tiny_lib::uint16_t port = 8888;
    tiny_lib::InetAddress server_address(ipaddr, port);
    //client_socket.Bind(server_address);

    client_socket.Connect(server_address);
    client_socket.SetNonBlocking();

    while(true){
        char buf[buf_size];  //在这个版本，buf大小必须大于或等于服务器端buf大小，不然会出错，想想为什么？
        bzero(&buf, sizeof(buf));
        //scanf("%s", buf);
        ssize_t write_bytes = write(client_socket.GetFd(), "hello", 5);
        if(write_bytes == -1){
            printf("socket already disconnected, can't write any more!\n");
            break;
        }
        bzero(&buf, sizeof(buf));
        ssize_t read_bytes = read(client_socket.GetFd(), buf, sizeof(buf));
        if(read_bytes > 0){
            printf("message from server: %s\n", buf);
        }else if(read_bytes == 0){
            printf("server socket disconnected!\n");
            break;
        }else if(read_bytes == -1){
            //close(sockfd);
            client_socket.Close();
           // errif(true, "socket read error");
        }
    }
    //close(sockfd);
    client_socket.Close();

    return 0;

}