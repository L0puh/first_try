#include <errno.h>
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
   struct sockaddr_in addr;
   bzero(&addr, sizeof(addr));
   addr.sin_family = AF_INET;
   addr.sin_port = htons(PORT);
   addr.sin_addr.s_addr = htonl(INADDR_ANY);
   if (connect(sock, (struct sockaddr*)&addr, sizeof(addr)) == -1)
      printf("%s\n", strerror(errno));
   struct test_data t;
   char* str = "message to the server";
   strcpy(t.info, str);
   t.id = 0;
   t.count = strlen(t.info);
   int bytes = 0;
   if (( bytes = send(sock, &t, sizeof(t), 0)) == -1)
      printf("%s\n", strerror(errno));
   printf("sent %d bytes: %s\n", bytes, t.info);
   close(sock);
   return 0;
}
