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
    uint8_t end = 64;
    data[data_size++] = 0x80; //1 bit
    
    while(data_size < end) 
        data[data_size++] = 0x00; // 0 bit

    uint64_t bitlen = data_size * 8;
	data[63] = bitlen;
	data[62] = bitlen >> 8;
	data[61] = bitlen >> 16;
	data[60] = bitlen >> 24;
	data[59] = bitlen >> 32;
	data[58] = bitlen >> 40;
	data[57] = bitlen >> 48;
	data[56] = bitlen >> 56;
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
