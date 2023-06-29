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
	while (true) 
	{
		
	
			char msg[256];
			int bytes = recv(it.Connection, msg, sizeof(msg), NULL);
			
			if (bytes > 0) { 
				std::cout << msg << std::endl;
				std::vector<Connection_t> conns;
				conns = *(it.Connections);
				it.send_message(&conns, msg);
		
		}
	}
	
}
void Socket::send_message(std::vector<Connection_t> *Connections,  char msg[256]) {
	std::vector<Connection_t> conns = *Connections; 
	for (int i = 0; i < conns.size(); i++) {
		send(conns.at(i).Connection, msg, sizeof(msg), NULL);
		
	}
}