#include "headers/net.h"
#include <netdb.h>
#include <string>
#include <sys/socket.h>


int connect_socket(struct addrinfo *servinfo) {
    int sockfd;
    struct addrinfo *p;
    for (p= servinfo; p != NULL; p=p->ai_next){
       sockfd = socket(p->ai_family, p->ai_socktype, p->ai_protocol);
       if (print_error(sockfd))
           continue;
       int conn = connect(sockfd, p->ai_addr, p->ai_addrlen);
       if (print_error(conn)){
           close(sockfd);
           continue;
       }
       break;
    } 
    char buff[INET_ADDRSTRLEN];
    void *addr = (struct sockaddr*)p->ai_addr;
    inet_ntop(p->ai_family, get_in_addr((struct sockaddr*)p->ai_addr), buff, INET_ADDRSTRLEN);
    printf("connected to: %s\n", buff);
    freeaddrinfo(servinfo);
    return sockfd;
}

int main () {
    struct addrinfo hints, *servinfo;
    hints = init_addrinfo(hints);
    int res = getaddrinfo(NULL, PORT, &hints, &servinfo);
    if (print_error(res))
        exit(1);
    int sockfd = connect_socket(servinfo);

    char buffer[MAXDATASIZE];
    while (true) {
        
        std::string message;
        std::getline(std::cin, message);
        int message_size = message.size();
        int bytes_sent = send(sockfd, (char *)&message_size, sizeof(int), 0);
        bytes_sent = send(sockfd, message.c_str(), message_size, 0);
        if (print_error(bytes_sent)){
            close(sockfd);
            exit(1);
        }
    }
    close(sockfd);
    return 0;
}


