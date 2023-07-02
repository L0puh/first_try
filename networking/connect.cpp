#include <sys/socket.h>
#include <netdb.h>
#include <sys/types.h>
#include <arpa/inet.h>
#include <iostream>
#include <cstring>


int main (){
    
    //create getaddrinfo
    struct addrinfo hints, *res;
    memset(&hints, 0, sizeof(hints));
    hints.ai_family = AF_UNSPEC;
    hints.ai_socktype = SOCK_STREAM;
    hints.ai_flags = AI_PASSIVE;
    if (int status = getaddrinfo(NULL, "3490", &hints, &res) < 0){
        std::cout << gai_strerror(status);
        return 1;
    }
    int sck = socket(res->ai_family, res->ai_socktype, res->ai_protocol);
    if (sck < 0 ){
        std::cout << strerror(errno);
        return 1;
    }
    int conn = connect(sck, res->ai_addr, res->ai_addrlen);
    if (conn < 0){
        std::cout << strerror(errno);
        return 1;
    }

    std::cout << "\nconnected\n";
}
