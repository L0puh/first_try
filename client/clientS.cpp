#include "clientS.h"

Socket::Socket() {
	this->init_socket();
}
Socket::~Socket() {
	close_socket();
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

	CreateThread(NULL, NULL, (LPTHREAD_START_ROUTINE)recieve_message, (LPVOID)(&Connection), NULL, NULL);
	// CreateThread(NULL, NULL, (LPTHREAD_START_ROUTINE)send_message, (LPVOID)(&Connection), NULL, NULL);
	
}

void Socket::send_message() {
	std::string message;
	while (true) {
		
		std::getline(std::cin, message);
		int message_size = message.size();
		send(this->Connection, (char*)&message_size, sizeof(int), NULL); // send size of msg first 
		send(this->Connection, message.c_str(), message_size, NULL);
	}
}
void Socket::recieve_message(SOCKET* Connection) {
	int message_size;
	
	while (true) {
		recv(*Connection, (char*)&message_size, sizeof(int), NULL);
		char* msg = new char[message_size + 1];
		msg[message_size] = '\0';
		int bytes = recv(*Connection, msg, message_size, NULL);
		if (bytes > 0) {
			std::cout << msg << std::endl;
		}
		delete[] msg;
	}

}
void Socket::close_socket() {
	closesocket(this->Connection);
	WSACleanup();	
}