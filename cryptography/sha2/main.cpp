#include "sha2.h"
#include <iostream>

int main () {
    SHA2 sha2;
    std::string data;
    std::getline(std::cin, data);
    

    sha2.init();
    sha2.update(reinterpret_cast<const uint8_t*> (data.c_str()), data.size());

    uint8_t *res = sha2.get_hash(); 
    char s[3];
    std::string hash;
	for (int i = 0; i < 32; i++) {
		sprintf(s, "%02x", res[i]);
		hash += s;
	}
    printf("%s\n", hash.c_str());

    delete[] res;
}
