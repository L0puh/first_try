#include "../headers/net.h"
Server::Server(){
    listen_server();
    while(true) {
        for (int i = 0; i != BACKLOG; i ++){
            socklen_t sin_size = sizeof(their_addr);
            int sockfd_client = accept(sockfd, (struct sockaddr *)&their_addr, &sin_size);
            
            if (print_error(sockfd_client))
                continue;

            inet_ntop(their_addr.sin_family, 
                    get_in_addr((struct sockaddr *)&their_addr), s, sizeof(s));
            printf("connection from: %s\n", s);
            
            connection_t conn;
            conn.index = i; conn.socketfd = sockfd_client;
            conn.name = recv_name(sockfd_client);
            connections.push_back(conn);
            std::string msg = "server: " + conn.name + " is connected";  
            send_msg(msg, sockfd_client);
            std::thread client(&Server::handle_client, this, sockfd_client, conn.name);   
            client.detach();
        } 
    }
}

Server::~Server(){
    close(sockfd_client);
    exit(1);
}
void Server::listen_server(){
    hints = init_addrinfo(this->hints);
    res = getaddrinfo(NULL, PORT, &hints, &servinfo);
    if (res != 0 ){
        fprintf(stderr, "getaddrinfo error: %s\n", gai_strerror(res));
        exit(1);
    }
    this->sockfd = create_socket(); 
    res = listen(sockfd, BACKLOG);

    if(print_error(res))
        exit(1);
}
int Server::create_socket(){
    int yes=1;
    for (this->p = this->servinfo; p != NULL; p = p->ai_next){

    sockfd = socket(p->ai_family, p->ai_socktype, p->ai_protocol);
    if (print_error(sockfd))
        continue;

    res = setsockopt(sockfd, SOL_SOCKET, SO_REUSEADDR, &yes, sizeof(int));
    if (print_error(res))
        exit(1); 

    res = bind(sockfd, p->ai_addr, p->ai_addrlen);
    if (print_error(res))
        exit(1);

    break; 
    }
    
    freeaddrinfo(servinfo);
    return sockfd;
}

std::string Server::recv_name(int current_socket){
    int name_size;
    int bytes_recv = recv(current_socket, (char*)&name_size, sizeof(int), 0);
    if (bytes_recv == -1) 
        exit(1);
    char *name = new char[name_size + 1];
    name[name_size] = '\0';
    bytes_recv = recv(current_socket, name, name_size, 0);
    std::string name_str = name;
    delete[] name;
    return name_str;
}
void Server::handle_client(int current_socket, std::string current_name){
        int msg_size, bytes_recv;
        bool is_over = false;   

        while ((bytes_recv = recv(current_socket, (char*)&msg_size, sizeof(int), 0)) != 0 && !is_over) {
                if (bytes_recv > 0 ) { 
                    char* msg = new char[msg_size+1];
                    msg[msg_size] = '\0';
                    bytes_recv = recv(current_socket, msg, msg_size, 0);
                    send_msg(msg, current_socket, current_name);
                    delete[] msg; 

                } else 
                    is_over = false;
            }
        close_connection(current_socket, &is_over);
}
void Server::send_msg(char* msg, int current_socket, std::string current_name){
    mtx.lock();
    std::string strmsg = msg;
    for (auto itr = connections.begin(); itr != connections.end(); itr++){
       if (current_socket != itr->socketfd ) { 
           if (strmsg.at(0) == '/' ){ // private msg: /<username> message
              std::string message = strmsg;
              message.erase(message.begin()); 
              std::string name;
              for (int i = 0; message.at(i) != ' '; i++){
                  name = name + message.at(i);
              }
              message.erase(0, name.size()+1);
              if (itr->name == name){
                   std::string private_msg = "<private> " + current_name + ": " + message;
                   size_t msg_size = private_msg.size();
                   int bytes_sent = send(itr->socketfd, &msg_size, sizeof(int), 0); 
                   bytes_sent = send(itr->socketfd, private_msg.c_str(), msg_size, 0); 
                   if (print_error(bytes_sent))
                       exit(1);
                   printf("!private message from %s (%d bytes) sent to %dth client\n", s,  bytes_sent, itr->index);
                   break;
              } continue;
           } else {  
               std::string nmsg = current_name + ": " + strmsg;
               size_t msg_size = nmsg.size();
               int bytes_sent = send(itr->socketfd, &msg_size, sizeof(int), 0); 
               bytes_sent = send(itr->socketfd, nmsg.c_str(), msg_size, 0); 
               if (print_error(bytes_sent))
                   exit(1);
               printf("message from %s (%d bytes) sent to %dth client\n", s,  bytes_sent, itr->index);
           }
       } else if (connections.size() == 1){
           char msg[26] = "server: the room is empty";
           int msg_size = sizeof(msg);
           int bytes_sent = send(itr->socketfd, &msg_size, sizeof(int), 0); 
           bytes_sent = send(itr->socketfd, msg, msg_size, 0); 
       } 
    }
    mtx.unlock();
}

void Server::send_msg(std::string msg, int current_socket){
    mtx.lock();
    size_t msg_size = sizeof(msg);
    for (auto itr = connections.begin(); itr != connections.end(); itr++){
       if (current_socket != itr->socketfd) { 
           int bytes_sent = send(itr->socketfd, &msg_size, sizeof(int), 0); 
           bytes_sent = send(itr->socketfd, msg.c_str(), msg_size, 0); 
           if (print_error(bytes_sent))
               exit(1);
        }
    }
    mtx.unlock();
}
void Server::close_connection(int current_socket, bool *is_over){
    printf("client(%d) is over\n", current_socket);
    std::vector<connection_t>::iterator itr = connections.begin();
    while (itr != connections.end()){
        if (itr->socketfd == current_socket){
            std::string msg = "server: " + itr->name + " is out";
            send_msg(msg, current_socket);
            mtx.lock();
            itr = connections.erase(itr);
            mtx.unlock();
            *is_over=true;
        } else 
            itr++;
    }
    close(current_socket);
}


struct addrinfo init_addrinfo(struct addrinfo hints){
    size_t size_hints = sizeof(hints);
    memset(&hints, 0, size_hints);
    hints.ai_family = AF_INET;
    hints.ai_socktype = SOCK_STREAM;
    hints.ai_flags = AI_PASSIVE;
    return hints;
}

bool print_error(int res){
    if (res == -1){
        fprintf(stderr, "server error: %s\n", strerror(errno));
        return true;
    }
    return false;
}

void *get_in_addr (struct sockaddr *sa){
    return &(((struct sockaddr_in*)sa)->sin_addr);  
}


