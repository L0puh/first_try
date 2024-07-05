#include <asm-generic/socket.h>
#include <netinet/in.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <strings.h>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <unistd.h>

struct test_data{
   char info[128];
   int id;
   int count;
};

int main(){

   int PORT = 8080;
   int sock = socket(AF_INET, SOCK_STREAM, 0);
   int en = 1;
   setsockopt(sock, SOL_SOCKET, SO_REUSEADDR, &en, sizeof(int));
   struct sockaddr_in addr;
   bzero(&addr, sizeof(addr));
   addr.sin_family = AF_INET;
   addr.sin_port = htons(PORT);
   addr.sin_addr.s_addr = htonl(INADDR_ANY);
   if (bind(sock, (struct sockaddr*)&addr, sizeof(addr)) == -1) exit(-1);
   if (listen(sock, 10) == -1) exit(-1);
   int bytes;
   int cli = accept(sock, 0, 0);
   printf("new connection\n");
   struct test_data t;
   if (( bytes = recv(cli, &t, sizeof(t), 0)) > 0){
      printf("[%d] %d: ", t.id, t.count);
      t.info[t.count] = '\0';
      printf("%s\n", t.info);
   }

   close(sock);
   return 0;
}
