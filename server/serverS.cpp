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

	for (int i = 0; i < 10; i++) {
		
		this->Connection = accept(sListen, (SOCKADDR*)&addr, &sizeofaddr);
		if (this->Connection != 0) {
			std::cout << "connection is success\n";
			Connection_t con;
			con.Connection = Connection; con.counter = i;
			this->Connections->push_back(con);
			this->index = i;
			
			CreateThread(NULL, NULL, (LPTHREAD_START_ROUTINE)recieve_message, (LPVOID)(this), NULL, NULL);
			
		}	
	}

}
Socket::~Socket() {
	for (int i = 0; i < 10; i++) {
		closesocket(this->Connections->at(i).Connection);
	}
}

void Socket::recieve_message(const Socket& it)
{
	int message_size = 0; 

	while (true) 
	{	
		recv(it.Connection, (char*)&message_size, sizeof(int), NULL);
		char* msg = new char[message_size + 1];
		msg[message_size] = '\0';
		
		int bytes = recv(it.Connection, msg, message_size, NULL);
			
		if (bytes > 0) { 
			std::cout << msg << std::endl;
			std::vector<Connection_t> conns;
			conns = *(it.Connections);
			
			it.send_message(&conns, msg, message_size, it.index);
		
		}
		else if (bytes == SOCKET_ERROR) {
			closesocket(it.Connection);
			
		}
		delete[] msg;
	}
	
}
void Socket::send_message(std::vector<Connection_t> *Connections,  char msg[], int msg_size, int index) {
	std::vector<Connection_t> conns = *Connections; 
	for (int i = 0; i < conns.size(); i++) {
		if (i == index) {
			continue;
		}
		send(conns.at(i).Connection, (char*)&msg_size, sizeof(int), NULL);
		send(conns.at(i).Connection, msg, msg_size, NULL);
		
	}
}