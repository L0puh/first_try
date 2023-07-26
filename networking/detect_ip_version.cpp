#include <arpa/inet.h>
#include <netinet/in.h>
#include <stdlib.h>
#include <stdio.h>
int main (int argc, char* argv[]) {
    char* str_addr = argv[1];
    char str[INET6_ADDRSTRLEN];
    unsigned char buf[sizeof(struct in6_addr)];
    if(inet_pton(AF_INET, str_addr,  buf) == 0){ 
        inet_pton(AF_INET6, str_addr,  buf);
        if (inet_ntop(AF_INET6, buf,str, sizeof(str))){
            printf("version in IPv6: %s\n", str);
        }
    } else{
        if (inet_ntop(AF_INET, buf,str, sizeof(str))){
            printf("version in IPv4: %s\n", str);
        }
    }
}

