#pragma once
#pragma comment(lib, "ws2_32.lib")
#include <WinSock2.h>
#include <iostream>
#include <vector>
#pragma warning(disable:4996)

struct Connection_t {
	SOCKET Connection;
	int counter;
};

class Socket {

private:
	SOCKET Connection;
	std::vector<Connection_t> Connections[10];
	
public:
	Socket();
	~Socket();
	
private:
	static void recieve_message(const Socket& it);
	static  void send_message(std::vector<Connection_t> *Connections, char msg[256]);
	
	
};