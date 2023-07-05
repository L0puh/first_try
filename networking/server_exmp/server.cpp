#include "headers/net.h"
#include <vector>
struct connection_t {
    int index;
    int socketfd;
};
std::vector<connection_t> connections;
int current_socket;
int create_socket(struct addrinfo *servinfo, struct addrinfo *p, int sockfd){
    int res, yes = 1;
    for (p = servinfo; p != NULL; p = p->ai_next){

       sockfd = socket(p->ai_family, p->ai_socktype, p->ai_protocol);
        
        if (print_error(sockfd))
            continue;
        
        res = setsockopt(sockfd, SOL_SOCKET, SO_REUSEADDR, &yes, sizeof(int));
        if (print_error(res))
            exit(1); 

        res = bind(sockfd, p->ai_addr, p->ai_addrlen);
        if (print_error(res)){
            close(sockfd);
            exit(1);
        }
    
        break; 
    }
    
    if(p == NULL){
        fprintf(stderr, "failed to bind: %s\n", strerror(errno));
        exit(1);
    }

    freeaddrinfo(servinfo);
    return sockfd;
}

int main () {
    struct addrinfo hints, *servinfo, *p;
    hints = init_addrinfo(hints);
    
    int res = getaddrinfo(NULL, PORT, &hints, &servinfo);
    if (res != 0 ){
        fprintf(stderr, "getaddrinfo error: %s\n", gai_strerror(res));
        return 1;
    }
    int sockfd;
    sockfd = create_socket(servinfo, p, sockfd); 
     
    res = listen(sockfd, BACKLOG);
    if (print_error(res))
        return 1;
    
    printf("wait for connection...\n");
    socklen_t sin_size;
    struct sockaddr_in their_addr;
    char s[INET_ADDRSTRLEN];
    for (int i = 0; i != BACKLOG; i ++){
        sin_size = sizeof(their_addr);
        int sockfd_new = accept(sockfd, (struct sockaddr *)&their_addr, &sin_size);
        if (print_error(sockfd_new)){
            continue;
        }
        connection_t conn;
        conn.index = i; conn.socketfd = sockfd_new;
        connections.push_back(conn);

        inet_ntop(their_addr.sin_family, 
                get_in_addr((struct sockaddr *)&their_addr), s, sizeof(s));
        printf("connection from: %s\n", s);
        
        pid_t thread = fork();
        if(!thread){
            
            current_socket = i;
            int msg_size;
            while (true) {

                //FIXME: add async receiving 
                for(int i = connections.size()-1; i != -1; i--) {

                    recv(connections.at(i).socketfd, (char*)&msg_size, sizeof(int), 0);
                    char* msg = new char[msg_size+1];
                    msg[msg_size] = '\0';
                    
                    int bytes_sent = recv(connections.at(i).socketfd, msg, msg_size, 0);
                    if (bytes_sent > 0 ){
                        printf("msg from client(%d): %s (size: %d bytes)\n", i, msg, msg_size);
                    }
                    else {
                        print_error(bytes_sent);
                        close(sockfd_new);
                        exit(1);
                    }
                     
                delete[] msg; 
            
                }
            }
        }
    } 
    return 0;
}







