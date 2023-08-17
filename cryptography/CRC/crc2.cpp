#include <cstdint>
#include <iostream>
#include <stdio.h>
#include <string>
#include <vector>

static const int width = sizeof(uint8_t) * 8;
static const int topbit = (1 << (width-1));
static const uint8_t polynomial = 0xDB;

std::vector<uint8_t> init(){
    std::vector<uint8_t> table;
    uint8_t rem;
    for (int div = 0; div < 256; div++) {
        rem = (div << (width - 8));
        for (uint8_t bit=8; bit > 0; bit--) {
            if (rem & topbit) {
                rem = (rem << 1) ^ polynomial;
            }
            else {
                rem = (rem << 1);
            }
        }
        table.push_back(rem);

    }
    return table;
}

uint8_t crc(uint8_t msg, std::vector<uint8_t> table, uint8_t rem) {
    uint8_t data;
    data = msg ^ (rem >> (width - 8));
    rem = table.at(data) ^ (rem << 8);
    return rem;
}

int main () {
    std::string msg;
    std::getline(std::cin, msg);
    
    std::vector<uint8_t> table = init();
    uint8_t res=0;
    for (const char c: msg) {
        res = crc(c, table, res);
        printf("%i\t", res);
    }

    //check
    if (crc(res, table, res ) == 0 ) {
        printf("success\n");
    }
    return 0;
}
