#ifndef NET_H
#define NET_H

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

#define PORT "3490"
#define BACKLOG 10
#define MAXDATASIZE 100

struct addrinfo init_addrinfo(struct addrinfo hints);
bool print_error(int res);
void *get_in_addr (struct sockaddr *sa);


#endif
