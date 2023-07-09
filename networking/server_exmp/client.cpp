#include "headers/net.h"

int send_msg(int sockfd);
int recv_msg(int sockfd);
int connect_socket(struct addrinfo *servinfo);
int send_name(int sockfd);

int main () {
    struct addrinfo hints, *servinfo;
    int res, sockfd;
    
    hints = init_addrinfo(hints);
    res = getaddrinfo(NULL, PORT, &hints, &servinfo);
    if (print_error(res))
        exit(1);
    
    sockfd = connect_socket(servinfo);

    send_name(sockfd); 
    std::thread recvth(recv_msg, sockfd);
    std::thread sndth(send_msg, sockfd);
    sndth.join();
    recvth.join();
    
    close(sockfd);
    return 0;
}


int send_name(int sockfd){
    printf("enter you name:\n");
    std::string name;
    std::getline(std::cin, name);
    size_t message_size = name.size();
    int bytes_sent = send(sockfd, (char *)&message_size, sizeof(int), 0);
    bytes_sent = send(sockfd, name.c_str(), message_size, 0);
    if (print_error(bytes_sent)){
        close(sockfd);
        exit(1);
    }
    return 0;
}
int send_msg(int sockfd){
    std::string message;
    while (true) {
        std::getline(std::cin, message);
        int message_size = message.size();
        int bytes_sent = send(sockfd, (char *)&message_size, sizeof(int), 0);
        bytes_sent = send(sockfd, message.c_str(), message_size, 0);
        if (print_error(bytes_sent)){
            close(sockfd);
            exit(1);
        }
    }
    return 0;
}
int recv_msg(int sockfd){
    while (true){  
        int msg_size, bytes_recv;
        bytes_recv = recv(sockfd, &msg_size, sizeof(int), 0);
        char *msg = new char[msg_size+1];
        msg[msg_size]='\0';
        bytes_recv = recv(sockfd, msg, msg_size, 0);
        if (print_error(bytes_recv))
            exit(1);
        printf("> %s\n", msg);
        delete[] msg;
    }
    return 0;
}
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

