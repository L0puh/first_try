#include "udp_node.h"

int main(int argc, char* argv[]){
   if (argc != 3) {
      printf("./run <my port> <their port>\n");
      exit(-1);
   }
   Node node;
   node.port = atoi(argv[1]);
   node.their_port = atoi(argv[2]);
   init_socket(&node);
   init_their_addr(&node);
   
   char buff[MAXLEN]; 
   socklen_t sz = sizeof(node.their_addr);
   int bytes = recvfrom(node.sockfd, buff, sizeof(buff), MSG_WAITALL, 
         (struct sockaddr*)&node.their_addr, &sz);
   buff[bytes+1] = '\0';
   printf("%s\n", buff);
}


