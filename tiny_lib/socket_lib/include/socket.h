#pragma once
#include <iostream>
#include "tiny_type.h"

//window header
#ifdef _WIN32
#include <windows.h>
#include <Winsock.h>
#endif // WIN32

//linux header
#ifdef __linux__
#include <sys/types.h>          /* header of socket */
#include <sys/socket.h>
#endif // __linux__


namespace tiny::mesh {		//mesh is from  
	
//define the main socket class
	class TinySocket {
	public:
		explicit TinySocket() = default;	
		virtual ~TinySocket() {};

		//init socket
		virtual tiny_int32_t InitSocket() = 0;

		//close socket
		virtual tiny_int32_t CloseSocket() = 0;
	};

	class TinyTcpSocket :public TinySocket {
	public:
		explicit TinyTcpSocket() = default;
		virtual ~TinyTcpSocket();

		/*breif : initialize the tcp socket
		* argument : none 
		* return : -1 or postive number
		*/
		tiny_int32_t InitSocket();
		tiny_int32_t CloseSocket() {
			return -1;
		}


	protected:
#ifdef _WIN32
		SOCKET socket_fd;
#endif

#ifdef __linux__
		tiny_int32_t socket_fd;
#endif // __linux__


		
	};


};