#include <sys/socket.h>
#include <sys/types.h>
#include <netdb.h>
#include <iostream>
#include <cstring>
int main (){
    int status, s;
    struct addrinfo hints, *res;
    memset(&hints, 0, sizeof(hints));
    hints.ai_socktype = SOCK_STREAM;
    hints.ai_family = AF_INET;
    hints.ai_protocol = 0;
    if (getaddrinfo("www.example.com", "http", &hints, &res) != 0){
        std::cout << "error in getaddrinfo:\n" << gai_strerror(status) << '\n';
        return 1;
    }
    s = socket(res->ai_family, res->ai_socktype, res->ai_protocol); 
    
    if (s < 0) {
        std::cout << "error in creating a socket:\n" << strerror(errno) << '\n'; 
        return 1;
    }
    std::cout << "socket created!\n";
    return 0;
}






























