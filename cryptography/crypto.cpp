#include <cstdlib>
#include <iostream>
#include <string>
#include <stdlib.h>

std::string generate_key(int msg_size) {
    std::string key;
    for (int i=0; i != msg_size; i++) {
        char k = rand();
        key += k;
    }
    return key;
}
int main () {
    std::string message;
    std::getline(std::cin, message);
    std::string K = generate_key(message.size());
    int C[message.size()];     
    for (int i =0; i != message.size(); i++) {
        C[i] =  message.at(i) ^ K.at(i);
    }

    std::string c_msg;
    for (int i =0; i != message.size(); i++){
        char sy = C[i] ^ K[i];
        c_msg += sy;
        std::cout << sy;
    }
    std::cout << '\n';
    return 0;
}

