#ifndef _INET_ADDRESS_H_
#define _INET_ADDRESS_H_


#include <arpa/inet.h>
#include <netinet/in.h>
#include <string>
#include <cstring>
#include "tiny_types.h"

//A class for inet address,which is designed as a hpp. No need cpp file

namespace tiny_lib{

// template<typename To, typename From>
// inline To implicit_cast(From const &f)
// {
//   return f;
// }

    class InetAddress{

    public:
        
        //to creat a InetAddress for accept
        InetAddress(){
            bzero(&addr_, sizeof(addr_));
            addr_len_ = 0;
        }

        //To create a InetAddress which required address and port
        explicit InetAddress(std::string& address, tiny_lib::uint16_t& port){

            bzero(&addr_, sizeof(addr_));
            addr_.sin_family = AF_INET;
            addr_.sin_addr.s_addr = inet_addr(address.c_str());
            addr_.sin_port = htons(port);
            addr_len_ = sizeof(addr_);
        }
        
        virtual ~InetAddress(){};

        //do not allow access and modify addr directly
        const sockaddr_in& GetAddr(){
            return addr_;
        }

        //return the struct sockaddr used type
        struct sockaddr* GetSockAddrType(){

            return reinterpret_cast<struct sockaddr*>(&addr_);
        }

        uint32_t& GetAddrLen(){
            
            return addr_len_;
        }

    protected:
        sockaddr_in addr_;      //socket address variable
        uint32_t addr_len_;   
    };


}

#endif