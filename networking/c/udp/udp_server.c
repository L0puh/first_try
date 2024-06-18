#include "udp_node.h"

int main(int argc, char* argv[]){
   if (argc != 3){
      printf("./run <my port> <their port>\n");
      exit(-1);
   }
   Node node;
   node.port = atoi(argv[1]);
   node.their_port = atoi(argv[2]);
   init_socket(&node);
   init_their_addr(&node);
   
   const char buff[MAXLEN] = "message from node";
   sendto(node.sockfd, buff, sizeof(buff), MSG_CONFIRM, 
         (const struct sockaddr*)&node.their_addr, 
          sizeof(node.their_addr));
}


