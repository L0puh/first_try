#pragma once
#pragma comment(lib, "ws2_32.lib")
#include <WinSock2.h>
#include <iostream>
#include <string>
#pragma warning(disable:4996)


class Socket {
private:
	SOCKET Connection;
	void init_socket();
	void close_socket();
public:
	Socket();
	~Socket();
	void send_message(std::string name);
	static void recieve_message(SOCKET *Connection); 
};