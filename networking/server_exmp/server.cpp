#include <netinet/in.h>
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
    
    status = bind(sock, res->ai_addr, res->ai_addrlen);
    listen(sock, 10);
    
    struct sockaddr_in their_addr;
    socklen_t addr_len = sizeof(their_addr);
    
    int new_sock = accept(sock, (struct sockaddr *)&their_addr, &addr_len);
    std::cout << "connected to a client\n";
    
    char const *msg = "Hello world";
    int len, bytes_sent;
    len = strlen(msg);
    bytes_sent = send(new_sock, msg, len, 0);
    
    std::cout << "bytes was sent: " << bytes_sent << '\n';
    if (bytes_sent < 0){
        std::cout << strerror(errno); 
        return 1;
    }
    close(new_sock);
    return 0;
}
