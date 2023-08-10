#include <iostream>
#include <string>
#include <bitset>


int main () {
    std::string message;
    std::getline(std::cin, message);
    std::bitset<8> block[message.size()];
    int n, i=0;
    for (const char c: message){
        n = c;
        block[i++] = std::bitset<8>(n);
    }
    for (int i = 0; i != message.size(); i++){
        std::bitset<8> x = block[i];
        n = 2;
        std::cout << "noraml:" << x << "\n"; 
        std::cout << "  rotr:" << ((x >> n) | (x << ((sizeof(x) << 3) - n))) << " \n";
    }

}


