#include <cmath>
#include <cstdlib>
#include <numeric>
#include <stdio.h>
#include <stdlib.h>
#include <system_error>
#include <vector>

int public_key, private_key;

unsigned get_prime();
unsigned encode(unsigned message, int n, int key);
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
    
    public_key=e;
    
    unsigned d=get_prime();
    while((d * e) % fi != 0) {
        d++;
    }

    private_key = d;

    printf("pub:  %d\npriv: %d\nn: %d\n", public_key, private_key, n);
    unsigned c = encode(32, n, public_key);
    unsigned m = encode(c, n, private_key);
    printf("encoded: %u, decoded: %u\n", c, m); 
    return 0;
}

unsigned encode(unsigned message, int n, int key) {
    unsigned res=0;
    res = std::fmod(std::pow(message, key), n);
    return res;
}

unsigned get_prime() 
{
    std::srand(time(0));
    unsigned r = 0;
    while (!is_prime(r)) {
        r = std::rand() % 100;
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
