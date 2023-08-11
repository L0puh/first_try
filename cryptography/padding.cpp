#include <iostream>
#include <stdlib.h>
#include <string>

uint8_t data[64];
int data_size = 0;

void update(const uint8_t *msg, size_t msg_size){
    for (int i=0; i < msg_size; i++)
        data[data_size++] = msg[i];
}

void pad(){
    uint64_t i = data_size;
    uint8_t end = 64;
    data[i++] = 0x80; //1 bit
    
    while(i < end) 
        data[i++] = 0x00; // 0 bit
}

int main () {
    std::string message;
    std::getline(std::cin, message);
    update(reinterpret_cast<const uint8_t*> (message.c_str()), message.size());
    pad();
    for (int i=0; i != 64; i++){
        printf("%i", data[i]);
    }
    return 0;
}
