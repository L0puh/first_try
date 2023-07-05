#include "../headers/net.h"

struct addrinfo init_addrinfo(struct addrinfo hints){
    size_t size_hints = sizeof(hints);
    memset(&hints, 0, size_hints);
    hints.ai_family = AF_INET;
    hints.ai_socktype = SOCK_STREAM;
    hints.ai_flags = AI_PASSIVE;
    return hints;
}

bool print_error(int res){
    if (res == -1){
        fprintf(stderr, "server error: %s\n", strerror(errno));
        return true;
    }
    return false;
}

void *get_in_addr (struct sockaddr *sa){
    return &(((struct sockaddr_in*)sa)->sin_addr);  
}


