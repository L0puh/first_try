/*
an attempt to implement the Diffie-Hellman protocol. 
the asymmetric encryption.
 */

#include <iostream>
#include <math.h>
#include <string>

class Bob{
    uint session_key;
    int Alice_key, kor, mod;
    public:
        Bob(int Alice_key, int kor, int mod);
        int init();
        void send_bob(int mesg[], int mes_size);
};
void Bob::send_bob(int mes[], int msg_size){
    std::string message;
    for (int i=0; i!=msg_size; i++){
        char sym = mes[i] ^ session_key;
        message += sym;

    }
    printf("message: %s\n", message.c_str());
}
int Bob::init(){
    const int secret_key = 8;
    int k = pow (kor, secret_key); 
    int Bob_key = k % mod;

    session_key = (int)pow(pow(kor, Alice_key), secret_key) % mod;
    return Bob_key;
}
Bob::Bob(int Ak, int k, int m){
    Alice_key = Ak;
    kor = k;
    mod = m;
}

int main () {
    const int secret_key = 13; 
    int kor = 2; int mod = 25;
    int Alice_key = (int)pow(kor, secret_key) % mod; // open key

    Bob bob(Alice_key, kor, mod);
    int Bob_key= bob.init();
    
    uint session_key = (int)pow((pow(kor, Bob_key)), secret_key ) % mod;
    std::string message;
    std::getline(std::cin, message);
    int c_message[message.size()];

    for (int i=0; i != message.size(); i++) {
        c_message[i] = ( message.at(i) ^ session_key);
    }
    bob.send_bob(c_message, message.size());
}
