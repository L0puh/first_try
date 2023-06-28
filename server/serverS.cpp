#include "serverS.h"

Socket::Socket(){
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

		this->Connection = accept(sListen, (SOCKADDR*)&addr, &sizeofaddr);
		if (this->Connection != 0) {
			std::cout << "connection is success\n";
			this->Connections[Connection];
			
			CreateThread(NULL, NULL, (LPTHREAD_START_ROUTINE)recieve_message, (LPVOID)(&Connection), NULL, NULL);
		}	
	}

}
Socket::~Socket() {
	for (int i = 0; i < 10; i++) {
		closesocket(this->Connections[i]);
	}
}
void Socket::recieve_message(SOCKET *Connection)
{
	while (true) {
		char msg[256];
		int bytes = recv(*Connection, msg, sizeof(msg), NULL);
		if (bytes > 0)
			std::cout << msg << std::endl;
	}
}
void Socket::send_message() {

}