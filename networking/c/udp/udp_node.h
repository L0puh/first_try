#ifndef NODE_H
#define NODE_H
#include <errno.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <strings.h>
#include <sys/socket.h>
#include <arpa/inet.h>

#define MAXLEN 4028

struct Node {
   int sockfd;
   int port, their_port;
   struct sockaddr_in my_addr;
   struct sockaddr_in their_addr;
};

typedef struct Node Node;

void init_socket(Node *node);
void init_their_addr(Node *node);

inline void init_socket(Node *node){
   node->sockfd = socket(AF_INET, SOCK_DGRAM, 0); 
   bzero(&node->my_addr, sizeof(node->my_addr));
   node->my_addr.sin_family = AF_INET;
   node->my_addr.sin_addr.s_addr = INADDR_ANY;
   node->my_addr.sin_port = htons(node->port);
   if (bind(node->sockfd, (const struct sockaddr*) &node->my_addr, 
            sizeof(node->my_addr)) == -1)
      printf("bind error\n");
}

inline void init_their_addr(Node *node){
   bzero(&node->their_addr, sizeof(node->their_addr));
   node->their_addr.sin_family = AF_INET;
   node->their_addr.sin_addr.s_addr = INADDR_ANY;
   node->their_addr.sin_port = htons(node->their_port);
}
#endif
