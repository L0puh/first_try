#include <assert.h>
#include <errno.h>
#include <netdb.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <strings.h>
#include <unistd.h>
#include <arpa/inet.h>
#include <sys/socket.h>
#include <netinet/in.h>

#define MAXLINE 4028

int8_t is_ipv4(char* ip){
   struct addrinfo info, *res;
   bzero(&info, sizeof(info));
   info.ai_socktype = SOCK_STREAM;
   info.ai_family = AF_UNSPEC;
   int status = 0;
   if (( status = getaddrinfo(ip, NULL, &info, &res)) != 0) {
      const char* error = gai_strerror(status);
      printf("error in getaddrinfo: %s\n", error);
      exit(-1);
   }
   for (struct addrinfo *p = res; p != NULL; p = res->ai_next){
      if (p->ai_family == AF_INET){
         printf("ipv4 is detected\n");
         return 1;
      } else if (p->ai_family == AF_INET6){
         printf("ipv6 is detected\n");
         return 0;
      }
   }
   return 0;
}

int main(int argc, char *argv[]){
   char* ip = "129.6.15.28";
   if (argc < 2) printf("no ip is provided\n");
   else ip = argv[1];

   if (!is_ipv4(ip)) exit(0);

   int sockfd, bytes;
   char buffer[MAXLINE+1];
   struct sockaddr_in servaddr;
   
   sockfd = socket(AF_INET, SOCK_STREAM, 0);
   assert(sockfd > 0);
  
   bzero(&servaddr, sizeof(servaddr));
   servaddr.sin_family = AF_INET;
   servaddr.sin_port = htons(13);
   assert(inet_pton(AF_INET, ip, &servaddr.sin_addr) > 0);
   int status = connect(sockfd, (const struct sockaddr *)&servaddr, sizeof(servaddr));
   if (status < 0) printf("error in connection: %s\n", strerror(errno));

   while ((bytes = read(sockfd, buffer, MAXLINE)) > 0){
      buffer[bytes] = '\0';
      printf("%d bytes recieved from %s: %s\n", bytes, ip, buffer);
   }
   return 0;
}
