#include <assert.h>
#include <stdio.h>
#include <unistd.h>
#include <arpa/inet.h>
#include <string.h>
#include <sys/socket.h>
#include <netinet/in.h>

#define MAXLINE 4028

int main(int argc, char *argv[]){
   char* ip = "129.6.15.28";
   if (argc < 2) printf("no ip is provided\n");
   else ip = argv[1];
   
   int sockfd, bytes;
   char buffer[MAXLINE+1];
   struct sockaddr_in servaddr;
   sockfd = socket(AF_INET, SOCK_STREAM, 0);
   assert(sockfd > 0);
   memset(&servaddr, 0, sizeof(servaddr));
   
   servaddr.sin_family = AF_INET;
   servaddr.sin_port = htons(13);
   assert(inet_pton(AF_INET, ip, &servaddr.sin_addr) > 0);
   assert(connect(sockfd, (const struct sockaddr *)&servaddr, sizeof(servaddr)) != -1);

   while ((bytes = read(sockfd, buffer, MAXLINE)) > 0){
      buffer[bytes] = '\0';
      printf("%d bytes recieved from %s: %s\n", bytes, ip, buffer);
   }

   return 0;
}
