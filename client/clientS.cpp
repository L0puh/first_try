#include "clientS.h"

Socket::Socket() {
	this->init_socket();
}
Socket::~Socket() {
	closesocket(this->Connection);
}

void Socket::init_socket() {
	WSAData wsaData;
	WORD DllVersion = MAKEWORD(2, 1);
	int res = WSAStartup(DllVersion, &wsaData);

	SOCKADDR_IN addr;
	int sizeofaddr = sizeof(addr);
	addr.sin_addr.s_addr = inet_addr("127.0.0.1");
	addr.sin_port = htons(1111);
	addr.sin_family = AF_INET;

	this->Connection = socket(AF_INET, SOCK_STREAM, NULL);
	res = connect(this->Connection, (SOCKADDR*)&addr, sizeofaddr);

	if (res == 0)
		std::cout << "connected to the server\n";

}

void Socket::send_message() {
	char message[256];
	std::cout << "enter a message: \n>";
	std::cin.getline(message, sizeof(message));
	send(this->Connection, message, sizeof(message), NULL);

}