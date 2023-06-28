#include "clientS.h"

int main(int argc, char* argv[]) {
	Socket socket;
	while (true) {
		socket.send_message();
	}
	return 0;
}


