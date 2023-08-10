#include <bitset>
#include <cstdint>
#include <string>
#include <stdlib.h>
#include <iostream>

std::bitset<32> rotr(std::bitset<32> x, uint32_t n) {
    return ((x >> n) | (x << ((sizeof(x) << 3) - n)));
}
std::bitset<32> sigma(std::bitset<32> x) {
    return rotr(x, 2) ^ rotr(x, 18) ^ (x >> 3);
}
std::bitset<32> choice(std::bitset<32> x){
    return (x ^ std::bitset<32>(2));
}
std::bitset<32> major(std::bitset<32> x){
    return (std::bitset<32>(4) & (x | std::bitset<32>(2))) | (x & std::bitset<32>(2));
}
int main () {
    std::string message;
    std::getline(std::cin, message);
    std::bitset<32> x[message.size()];    
    int i=0;
    for (const char c: message) {
        x[i] = std::bitset<32>((int)c);
        sigma(x[i]);
        std::cout << "sigma   " << sigma(x[i]) << "\n";
        std::cout << "choice  " << choice(x[i]) << "\n";
        std::cout << "major   " <<major(x[i]) << '\n';
        std::cout << c << "       " << x[i]<< "\n\n";

        i++;
    }
    return 0;
}
