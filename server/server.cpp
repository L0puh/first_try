#pragma comment(lib, "ws2_32.lib")
#include <WinSock2.h>
#include <iostream>
#pragma warning(disable:4996)

int main(int argc, char* argv[]) {
	WSAData wsaData;
	WORD DllVersion = MAKEWORD(2, 1); // choose a version of winsock
	if (WSAStartup(DllVersion, &wsaData) != 0) { // start the lib
		std::cout << "error" << std::endl;
		return -1;
	}
	SOCKADDR_IN addr; // storage for the address 
	int sizeofaddr = sizeof(addr);
	addr.sin_addr.s_addr = inet_addr("127.0.0.1"); // ip address
	addr.sin_port = htons(1111); // port for identification the programm 
	addr.sin_family = AF_INET; // family of internet protocols

	SOCKET sListen = socket(AF_INET, SOCK_STREAM, NULL); // create the socket

	// link the address to the socket
	// get the socket, the link to address and size
	bind(sListen, (SOCKADDR*)&addr, sizeof(addr));

	listen(sListen, SOMAXCONN); // start listening, 
	// gets the socket and max limit of requests

	SOCKET newConnection;
	// keep data of connection 
	newConnection = accept(sListen, (SOCKADDR*)&addr, &sizeofaddr); 

	if (newConnection == 0) {
		std::cout << "error in connection\n";
	}
	else {
		std::cout << "connection is success\n";
		char msg[] = "hello world";
		send(newConnection, msg, sizeof(msg), NULL);
	}
	 

	return 0;
}