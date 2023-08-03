#include "socket.h"

namespace tiny::mesh {

	//destruct for TinyTcpSocket
	TinyTcpSocket::~TinyTcpSocket() {

	}

	tiny_int32_t TinyTcpSocket::InitSocket() {

		//win32 api
#ifdef _WIN32

		//windows socket api basic operation
		// Initialize Windows socket library
		WSADATA     wsaData;
		//SOCKET       sListen, sClient;
		//SOCKADDR_IN local, client;
		//int         iaddrSize = sizeof(SOCKADDR_IN);
		//DWORD       dwThreadId;
		WSAStartup(0x0202, &wsaData);

		//creat a socket;
		socket_fd = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);
#endif

		return socket_fd;
	}


}