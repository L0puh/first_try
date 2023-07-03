
#include <sys/socket.h>
#include <netdb.h>
#include <sys/types.h>
#include <arpa/inet.h>
#include <cstring>
#include <iostream>
#include <unistd.h>
int main () {

    struct addrinfo hints, *res;
    int sock;
    memset(&hints, 0, sizeof(hints));
    hints.ai_family = AF_INET;
    hints.ai_socktype = SOCK_STREAM;
    hints.ai_flags = AI_PASSIVE;   
    int status = getaddrinfo(NULL, "3490", &hints, &res);

    sock = socket(res->ai_family, res->ai_socktype, res->ai_protocol);
    int conn = connect(sock, res->ai_addr, res->ai_addrlen);
    
    if (conn < 0){
        std::cout << strerror(errno) << '\n';
        return 1;
    }
    std::cout<<"client is connected!\n";

    char *buffer;
    int len;
    len = sizeof(buffer);
    int bytes_recv = recv(sock, buffer, len, 0);
    std::cout << "message: " << buffer << '\n';
    close(conn);
    return 0;
}















