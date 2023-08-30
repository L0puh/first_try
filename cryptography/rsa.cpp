#include <cmath>
#include <cstdlib>
#include <ctime>
#include <numeric>
#include <stdio.h>
#include <stdlib.h>
#include <random>
#include <string>
#include <vector>


void print_vector(std::vector<unsigned> msg);
std::string decode(std::vector<unsigned> c_msg, int n, int d);
std::vector<unsigned> encode(std::string message, int n, int e);
int modular_pow(int base, int modulus, int exponent);
unsigned get_prime();
bool is_prime(int n);

int main () {
    unsigned p, q, n, fi;
    
    p = get_prime();
    q = get_prime();

    n = p * q; 
    fi=(p-1)*(q-1);
    
    int e=get_prime();
    while(std::gcd(e, fi) != 1) 
        e++;
    
    int d = 1;
    while ((d * e) % fi != 1) {
        d++;
    }

    std::string message = "hello world!";
    std::vector<unsigned> c_msg = encode(message, n, e);
    print_vector(c_msg);
    printf("%s\n", decode(c_msg, n, d).c_str());

    return 0;
    
}

void print_vector(std::vector<unsigned> msg) {
    for (auto itr=msg.begin(); itr != msg.end(); itr++){
        printf("%d", *itr);
    }
}
std::string decode(std::vector<unsigned> c_msg, int n, int d) {
    std::string msg;
    for (auto itr=c_msg.begin(); itr != c_msg.end(); itr++){
        char c = modular_pow(*itr, n, d);
        msg += c;
    }
    printf("\n\n");
    return msg;
}
std::vector<unsigned> encode(std::string message, int n, int e){
    std::vector<unsigned> ciph;
    for (const char c: message) {
        ciph.push_back(modular_pow(c, n, e));
    }
    print_vector(ciph);
    return ciph;
}

int modular_pow(int base, int modulus, int exponent) {
    int result = 1;
    while (exponent > 0) {
        if (exponent % 2 == 1) {
            result = (result * base) % modulus;
        }
        exponent = exponent >> 1;
        base = (base * base) % modulus;
    }
    return result;
}

unsigned get_prime() {
    std::random_device rd;
    std::mt19937 generator(rd());
    std::uniform_int_distribution<int> distribution(10, 100);
    unsigned r = 0;
    while (!is_prime(r)) {
        r = distribution(generator);
    }
    return r;
}

bool is_prime(int n) {
    if (n <= 1)
        return false;
    for (int i = 2; i <= std::sqrt(n); i++) {
        if (n % i == 0)
            return false;
    }
    return true;
}
