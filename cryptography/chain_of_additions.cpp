#include <iostream>
#include <sys/types.h>

ulong add(ulong a, ulong x, ulong n) {
    // a ^ x mod n
    ulong s = 1;
    while(x) {
        if (x & 1) 
            s = (s * a) % n;

        x = (x >> 1);
        a = (a * a) % n;
    }
    return s;
}
int main () {
    // 18 ^ 49 mod 23
    std::cout << add(14, 49, 23) << '\n';
    return 0;
}
