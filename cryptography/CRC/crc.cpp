#include <iostream>
#include <stdlib.h>
#include <stdio.h>
#include <string>
#include <vector>

#define WIDTH (8 * sizeof(uint8_t))
#define TOPBIT (1 << (WIDTH - 1))

const int polynomail = 0xD8; 

uint8_t crc(uint8_t message, uint8_t remainder) {
    remainder ^= (message  << (WIDTH - 8));
    for (uint8_t bit=8; bit > 0; bit--){
        if (remainder & TOPBIT) 
            remainder = (remainder << 1) ^ polynomail;
        else 
            remainder = (remainder << 1);
        remainder = remainder;
    }
    return remainder;
}

int main () {
    std::string msg;
    std::getline(std::cin, msg);
    std::vector<uint8_t> remainder;
    uint8_t rem=0;
    
    // compress the data (get remainder)
    for (const char c: msg) {
        rem = crc(c, 0);
        remainder.push_back(rem);
    }

    //check the data
    for (auto itr = remainder.begin(); itr != remainder.end(); itr++){
        rem = crc(*itr, *itr);
        if (rem != 0){
            printf("error\n");
            exit(1);
        }
    }
    printf("succes\n");
    return 0;
}
