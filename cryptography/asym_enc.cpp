/*
an attempt to implement the Diffie-Hellman protocol. 
the asymmetric encryption.
 */

#include <iostream>
#include <math.h>
#include <string>

long generate_key(){
    return rand() % 99999999999999999;
}

class Bob{
    ulong session_key;
    long Alice_key, primitive, mod;
    public:
        Bob(long Alice_key, long primitive, long mod);
        long init();
        void send_bob(long mesg[], long mes_size);
};
void Bob::send_bob(long mes[], long msg_size){
    std::string message;
    for (long i=0; i!=msg_size; i++){
        char sym = mes[i] ^ session_key;
        message += sym;
    }
    printf("message: %s\n | key : %lu\n", message.c_str(), session_key);
}
long Bob::init(){
    const long secret_key = generate_key();
    long k = pow (primitive, secret_key); 
    long Bob_key = k % mod;
    session_key = (long)pow( Alice_key, secret_key) % mod;
    return Bob_key;
}
Bob::Bob(long Ak, long k, long m){
    Alice_key = Ak;
    primitive = k;
    mod = m;
}

int main () {
    const long secret_key = generate_key(); 
    long primitive = generate_key(); long mod = generate_key();
    long Alice_key = (long)pow(primitive, secret_key) % mod; // open key

    Bob bob(Alice_key, primitive, mod);
    long Bob_key= bob.init();
    
    ulong session_key = (long)pow( Bob_key, secret_key ) % mod;
    std::string message;
    std::getline(std::cin, message);
    long c_message[message.size()];
    for (long i=0; i != message.size(); i++) {
        c_message[i] = ( message.at(i) ^ session_key);
    }
    bob.send_bob(c_message, message.size());
}
