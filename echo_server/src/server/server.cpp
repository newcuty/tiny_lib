
#include <thread>
//#include "server.h"
#include "socket.h"
#include "inet_address.hpp"
#include "epoll.h"


const int buf_size = 1024;

void handleReadEvent(int sockfd){
    char buf[buf_size];
    while(true){    
        bzero(&buf, sizeof(buf));
        ssize_t bytes_read = read(sockfd, buf, sizeof(buf));
        if(bytes_read > 0){
            printf("message from client fd %d: %s\n", sockfd, buf);
            write(sockfd, buf, sizeof(buf));
        } else if(bytes_read == -1 && errno == EINTR){  //if client exit normally, continue to read data
            printf("continue reading");
            continue;
        } else if(bytes_read == -1 && ((errno == EAGAIN) || (errno == EWOULDBLOCK))){
            printf("finish reading once, errno: %d\n", errno);
            break;
        } else if(bytes_read == 0){  //EOF, client lose connection
            printf("EOF, client fd %d disconnected\n", sockfd);
            close(sockfd);   //close the socket
            break;
        }
    }
}

int main(int argc, char** argv){

    //construct the socket and 
    tiny_lib::net::Socket server_socket;
    tiny_lib::net::Epoll server_epoll;

    std::vector<tiny_lib::net::Socket> clients_;
    //clients_.resize(10);
    
    std::string ipaddr("127.0.0.1"); 
    tiny_lib::uint16_t port = 8888;
    tiny_lib::InetAddress server_address(ipaddr, port);
    server_socket.Bind(server_address);
    server_socket.Listen();
    server_socket.SetNonBlocking();

    EPOLL_EVENTS event = static_cast<EPOLL_EVENTS>(EPOLLIN | EPOLLET);
    server_epoll.AddFd(server_socket.GetFd(), event);

    std::thread thread_poll([&](){

        while (1)
        {
            //get the epoll wait event
            std::vector<tiny_lib::net::EpollEvent> activeEvents = server_epoll.Poll();
        
            for(uint32_t i = 0; i < activeEvents.size(); i++){

                //the server fd == the fd of active event means there is an new connection
                if(activeEvents[i].data.fd == server_socket.GetFd()){
                    
                    //create the client socket 
                    tiny_lib::InetAddress client_address;        
                    tiny_lib::net::Socket& client_socket = server_socket.Accept(client_address);
                
                    clients_.push_back(client_socket);

                    //client_socket.SetNonBlocking();

                    printf("new client fd %d! IP: %s Port: %d\n", clients_[i].GetFd(), 
                        inet_ntoa(client_address.GetAddr().sin_addr), ntohs(client_address.GetAddr().sin_port));

                    //add the client socket into epoll list
                    EPOLL_EVENTS event = static_cast<EPOLL_EVENTS>(EPOLLIN | EPOLLET);
                    server_epoll.AddFd(clients_[i].GetFd(), event);

                }else if (activeEvents[i].events & EPOLLIN){

                    std::cout << "incoming message\n";
                    handleReadEvent(activeEvents[i].data.fd);

                }else{

                    std::cout << "to be finished\n";

                }

            }
        }

    });

    thread_poll.join();
    // tiny_lib::InetAddress client_address;
    // server_socket.Accept(client_address);

  


    return 0;
}
