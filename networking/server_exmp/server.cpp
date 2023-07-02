#include <sys/socket.h>
#include <netdb.h>
#include <sys/types.h>
#include <arpa/inet.h>
#include <cstring>
#include <iostream>

int main () {

    struct addrinfo hints, *res;
    int sock;
    memset(&hints, 0, sizeof(hints));
    hints.ai_family = AF_INET;
    hints.ai_socktype = SOCK_STREAM;
    hints.ai_flags = AI_PASSIVE;    
    int status = getaddrinfo(NULL, "3490", &hints, &res);
    sock = socket(res->ai_family, res->ai_socktype, res->ai_protocol);
    
    bind(sock, res->ai_addr, res->ai_addrlen);
    listen(sock, 10);
    std::cout << "binded\n";   
    struct sockaddr_storage their_addr;
    socklen_t addr_len = sizeof(their_addr);
    int new_sock = accept(sock, (struct sockaddr *)&their_addr, &addr_len);
    if (new_sock < 0){
        std::cout << strerror(errno); 
        return 1;
    }
    std::cout << "accepted\n";
    return 0;
}
