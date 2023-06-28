#pragma comment(lib, "ws2_32.lib")
#include <WinSock2.h>
#include <iostream>
#pragma warning(disable:4996)

SOCKET Connection;
SOCKET Connections[3];

void receive_messages(SOCKET Connection);

int main(int argc, char* argv[]) {
	WSAData wsaData;
	WORD DllVersion = MAKEWORD(2, 1); 
	WSAStartup(DllVersion, &wsaData);
	
	SOCKADDR_IN addr;
	int sizeofaddr = sizeof(addr);
	addr.sin_addr.s_addr = inet_addr("127.0.0.1"); 
	addr.sin_port = htons(1111); 
	addr.sin_family = AF_INET; 

	SOCKET sListen = socket(AF_INET, SOCK_STREAM, NULL); 
	bind(sListen, (SOCKADDR*)&addr, sizeof(addr));
	listen(sListen, SOMAXCONN); 
	
	
	for (int i = 0; i < 3; i++) {

		Connection = accept(sListen, (SOCKADDR*)&addr, &sizeofaddr);
		if (Connection != 0) {
			std::cout << "connection is success\n";
			Connections[Connection];
			CreateThread(NULL, NULL, (LPTHREAD_START_ROUTINE)receive_messages, (LPVOID)(Connection), NULL, NULL);
		}
	}
	return 0;
}

void receive_messages(SOCKET Connection)
{
	while (true) {
		char msg[256];
		int bytes = recv(Connection, msg, sizeof(msg), NULL);
		if (bytes > 0)
			std::cout << msg << std::endl;
	}
}