#pragma once
#pragma comment(lib, "ws2_32.lib")
#include <WinSock2.h>
#include <iostream>
#pragma warning(disable:4996)


class Socket {
private:
	SOCKET Connection;
	void init_socket();
public:
	Socket();
	~Socket();
	void send_message();
	


};