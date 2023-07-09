#ifndef NET_H
#define NET_H

#include <vector>
#include <thread>
#include <mutex>
#include <csignal>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <errno.h>
#include <string.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <netdb.h>
#include <arpa/inet.h>
#include <iostream>

#define PORT "3490"
#define BACKLOG 10
#define MAXDATASIZE 100

struct addrinfo init_addrinfo(struct addrinfo hints);
void *get_in_addr (struct sockaddr *sa);
bool print_error(int res);

struct connection_t {
    int index;
    std::string name;
    int socketfd;
};

class Server{
    private:
        std::mutex mtx;
        struct sockaddr_in their_addr;
        char s[INET_ADDRSTRLEN];
        int sockfd, sockfd_client, res;
        std::vector<connection_t> connections;
        struct addrinfo hints, *servinfo, *p;
        
        void handle_client(int current_socket, std::string current_name);
        std::string recv_name(int current_socket);
        void close_connection(int current_socket, bool *is_over);
        void listen_server();
        int create_socket();
        
        std::string get_username(std::string *message);
        void send_msg(std::string msg, int current_socket, std::vector<connection_t>::iterator it);
        void send_msg(std::string msg, int current_socket);
        void send_msg(char* msg, int current_socket, std::string current_name);
    public: 
        Server();
        ~Server();
};



#endif
