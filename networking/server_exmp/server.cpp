#include "headers/net.h"

std::mutex mtx;

struct connection_t {
    int index;
    int socketfd;
};

std::vector<connection_t> connections;

void send_msg(std::string msg, int current_socket);
void handle_client(int current_socket);
void close_connection(int current_socket, bool *is_over);
int create_socket(struct addrinfo *servinfo, struct addrinfo *p, int sockfd);
void send_msg(char* msg, int msg_size, int current_socket);

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
    
    socklen_t sin_size;
    struct sockaddr_in their_addr;
    char s[INET_ADDRSTRLEN];
    
    while(true) {
        for (int i = 0; i != BACKLOG; i ++){
            sin_size = sizeof(their_addr);
            int sockfd_new = accept(sockfd, (struct sockaddr *)&their_addr, &sin_size);
            
            if (print_error(sockfd_new))
                continue;

            connection_t conn;
            conn.index = i; conn.socketfd = sockfd_new;
            connections.push_back(conn);

            inet_ntop(their_addr.sin_family, 
                    get_in_addr((struct sockaddr *)&their_addr), s, sizeof(s));
            printf("connection from: %s\n", s);
            send_msg("server: new connection", sockfd_new);
            std::thread client(handle_client, sockfd_new);   
            client.detach();
        } 
    }
    return 0;
}

void handle_client(int current_socket){
        int msg_size, bytes_recv;
        bool is_over = false;   

        while ((bytes_recv = recv(current_socket, (char*)&msg_size, sizeof(int), 0)) != 0 && !is_over) {
                if (bytes_recv > 0 ) { 
                    char* msg = new char[msg_size+1];
                    msg[msg_size] = '\0';
                    bytes_recv = recv(current_socket, msg, msg_size, 0);
                    send_msg(msg, msg_size, current_socket);
                    delete[] msg; 

                } else 
                    is_over = false;
            }
        close_connection(current_socket, &is_over);
}
void send_msg(char* msg, int msg_size, int current_socket){
    mtx.lock();
    for (auto itr = connections.begin(); itr != connections.end(); itr++){
       if (current_socket != itr->socketfd) { 
           int bytes_sent = send(itr->socketfd, &msg_size, sizeof(int), 0); 
           bytes_sent = send(itr->socketfd, msg, msg_size, 0); 
           if (print_error(bytes_sent))
               exit(1);
           printf("message(%d bytes) sent to %dth client: %s\n", bytes_sent, itr->index, msg);
       } else if (connections.size() == 1){
           char msg[26] = "server: the room is empty";
           int msg_size = sizeof(msg);
           int bytes_sent = send(itr->socketfd, &msg_size, sizeof(int), 0); 
           bytes_sent = send(itr->socketfd, msg, msg_size, 0); 
       } 
    }
    mtx.unlock();
}

void send_msg(std::string msg, int current_socket){
    mtx.lock();
    size_t msg_size = sizeof(msg);
    for (auto itr = connections.begin(); itr != connections.end(); itr++){
       if (current_socket != itr->socketfd) { 
           int bytes_sent = send(itr->socketfd, &msg_size, sizeof(int), 0); 
           bytes_sent = send(itr->socketfd, msg.c_str(), msg_size, 0); 
           if (print_error(bytes_sent))
               exit(1);
           printf("message(%d bytes) sent to %dth client: %s\n", bytes_sent, itr->index, msg.c_str());
        }
    }
    mtx.unlock();
}
void close_connection(int current_socket, bool *is_over){
    printf("client(%d) is over\n", current_socket);
    std::vector<connection_t>::iterator itr = connections.begin();
    while (itr != connections.end()){
        if (itr->socketfd == current_socket){
            mtx.lock();
            itr = connections.erase(itr);
            mtx.unlock();
            send_msg("server: someone has disconnected", current_socket);
            *is_over=true;
        } else 
            itr++;
    }
    close(current_socket);
}

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

