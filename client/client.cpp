#pragma comment(lib, "ws2_32.lib")
#include <WinSock2.h>
#include <iostream>
#pragma warning(disable:4996)

void send_message(SOCKET Connection);

int main(int argc, char* argv[]) {
	
	WSAData wsaData;
	WORD DllVersion = MAKEWORD(2, 1); 
	int res = WSAStartup(DllVersion, &wsaData);  


	SOCKADDR_IN addr; 
	int sizeofaddr = sizeof(addr);
	addr.sin_addr.s_addr = inet_addr("127.0.0.1"); 
	addr.sin_port = htons(1111); 
	addr.sin_family = AF_INET; 

	SOCKET Connection = socket(AF_INET, SOCK_STREAM, NULL);
	res = connect(Connection, (SOCKADDR*)&addr, sizeofaddr);

	if (res == 0)
		std::cout << "connected to the server\n";

	while(true)
		send_message(Connection);

	return 0;
}


void send_message(SOCKET Connection) {
	char message[256];
	std::cout << "enter a message: \n>";
	std::cin.getline(message, sizeof(message));
	send(Connection, message, sizeof(message), NULL);
	
}