#pragma once
#pragma comment(lib, "ws2_32.lib")
#include <WinSock2.h>
#include <iostream>
#pragma warning(disable:4996)

class Socket {

private:
	SOCKET Connection;
	SOCKET Connections[10];
public:
	Socket();
	~Socket();

private:
	static void recieve_message(SOCKET* Connection);
	void send_message();

};