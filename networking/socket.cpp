#include <netinet/in.h>
#include <sys/socket.h>
#include <sys/types.h>
#include <arpa/inet.h>
#include <netdb.h>
#include <iostream>
#include <cstring>

int print_error(int status);

int main (){
    int status, descriptor;
    struct addrinfo hints, *res;
    memset(&hints, 0, sizeof(hints));
    hints.ai_socktype = SOCK_STREAM;
    hints.ai_family = AF_UNSPEC;
    hints.ai_flags = AI_PASSIVE;
    if (getaddrinfo(NULL, "3490", &hints, &res) != 0){
        std::cout << "error in getaddrinfo:\n" << gai_strerror(status) << '\n';
        return 1;
    }
    descriptor = socket(res->ai_family, res->ai_socktype, res->ai_protocol); 
    if (print_error(descriptor))
        return 1;
    std::cout << "socket created!\n";

    int s = bind(descriptor, res->ai_addr, res->ai_addrlen);
    if (print_error(s))
        return 1;
    char str_addr[INET_ADDRSTRLEN];
    void *addr = &(((struct sockaddr_in *)res->ai_addr)->sin_addr);
    std::cout << "socket binded to: " << inet_ntop(res->ai_family, addr, str_addr, sizeof(str_addr)) << '\n';
     
    return 0;
}

int print_error(int status) {
    if (status < 0){
        std::cout << "error: " << strerror(errno) << '\n';
        return 1;
    }
    return 0;
}
