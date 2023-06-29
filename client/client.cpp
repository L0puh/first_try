#include "clientS.h"

int main(int argc, char* argv[]) {
	std::string name; 
	std::getline(std::cin, name);

	Socket socket;
	socket.send_message(name);
	return 0;
}


