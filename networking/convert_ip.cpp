// convert string address to ip version IPv4 or IPv6

#include <arpa/inet.h>
#include <cstring>
#include <sys/socket.h> 
#include <netdb.h>
#include <iostream> 

int main (int argc, char *argv[]){
    int status;
    struct addrinfo hints, *res;
    memset(&hints, 0, sizeof(hints));
    hints.ai_socktype = SOCK_STREAM;
    hints.ai_family = AF_UNSPEC;
    if ((status = getaddrinfo(argv[1], NULL, &hints, &res)) != 0 ){
        std::cout << "error in getaddrinfo: " << gai_strerror(status) << '\n';
        exit(1);
    }
    
    std::cout << "getaddrinfo is working!\n";
    char ipstr[INET_ADDRSTRLEN];
    for (struct addrinfo *p = res; p != NULL; p = res->ai_next){
        switch(p->ai_family){
        case AF_INET: {  
            struct sockaddr_in *ipv4 = (struct sockaddr_in *)p->ai_addr;
            void* addr = &(ipv4->sin_addr);
            inet_ntop(AF_INET, addr, ipstr, INET_ADDRSTRLEN);
            std::cout << "IP: " << ipstr << std::endl;
            return 0;
        }
        case AF_INET6: {
            struct sockaddr_in6 *ipv6 = (struct sockaddr_in6 *)p->ai_addr;
            void* addr6 = &(ipv6->sin6_addr);
            inet_ntop(AF_INET6, addr6, ipstr, INET_ADDRSTRLEN);
            std::cout << "IP: " << ipstr << std::endl;
            return 0;
        }
        default:
            std::cout << "can't recognize the AF\n";
            return 0;
        }
    }
    freeaddrinfo(res);
    
    return 0;
}

