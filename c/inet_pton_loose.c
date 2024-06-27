#include <arpa/inet.h>
#include <netinet/in.h>
#include <stdio.h>

int main(int argc, char* argv[]) {
   if (argc != 2) {
      printf("USAGE: ./run <IP>\n"); 
      return 0;
   }
   int res;
   char* addr = argv[1];
   struct in_addr val;
   char buff[INET6_ADDRSTRLEN];
   if (inet_pton(AF_INET, addr, buff) == 0){
      printf("invalid inet pton for IPv6\n");
      if((res = inet_aton(addr, &val)) > 0) {
         inet_ntop(AF_INET, &val, buff, INET_ADDRSTRLEN);
         printf("valid aton: IPv6 -> IPv4: %s\n", buff);
      } else if (res == 0)
         printf("invalid inet aton for IPv6\n");
   } else if (inet_pton(AF_INET6, addr, buff) == 0){
      printf("invalid inet pton for IPv4\n");
      if((res = inet_aton(addr, &val)) > 0) {
         inet_ntop(AF_INET6, &val, buff, INET6_ADDRSTRLEN);
         printf("valid aton: IPv4 -> IPv6: %s\n", buff);
      } else if (res == 0)
         printf("invalid inet aton for IPv4\n");
   }

   return 0;
}
