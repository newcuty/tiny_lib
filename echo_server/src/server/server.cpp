#include "server.h"
#include "socket.h"
#include "inet_address.hpp"

int main(int argc, char** argv){

    //创建对象
    tiny_lib::net::Socket server_socket;
    
    //
    std::string ipaddr("127.0.0.1"); 
    tiny_lib::uint16_t port = 8888;
    tiny_lib::InetAddress server_address(ipaddr, port);
    server_socket.Bind(server_address);
    server_socket.Listen();

    tiny_lib::InetAddress client_address;
    server_socket.Accept(client_address);


    return 0;
}