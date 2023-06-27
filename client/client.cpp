#pragma comment(lib, "ws2_32.lib")
#include <WinSock2.h>
#include <iostream>
#pragma warning(disable:4996)
 
int print_error(int result);
void print_message(SOCKET Connection);

int main(int argc, char* argv[]) {
	WSAData wsaData;
	WORD DllVersion = MAKEWORD(2, 1); // choose version to winsock
	int res = WSAStartup(DllVersion, &wsaData);  // start the lib
	print_error(res);

	SOCKADDR_IN addr; // storage for the address 
	int sizeofaddr = sizeof(addr);
	addr.sin_addr.s_addr = inet_addr("127.0.0.1"); // ip address
	addr.sin_port = htons(1111); // port for identification the programm 
	addr.sin_family = AF_INET; // family of internet protocols

	SOCKET Connection = socket(AF_INET, SOCK_STREAM, NULL);
	res = connect(Connection, (SOCKADDR*)&addr, sizeofaddr);
	
	if (res == 0) 
		std::cout << "connected to the server\n";
	else 
		print_error(res);

	
	print_message(Connection);

	return 0;
}

int print_error(int result) {
	if (result != 0) {
		std::cout << "error in client" << std::endl;
		return 1;
	}
}
void print_message(SOCKET Connection) {
	char msg[200];
	recv(Connection, msg, sizeof(msg), NULL);
	std::cout << "\nmessage from the server: " << msg << std::endl;
}