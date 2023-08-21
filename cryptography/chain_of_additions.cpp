#include <iostream>
#include <sys/types.h>


ulong add(ulong a, ulong x, ulong n) {
    // a ^ x mod n
    ulong s = 1;
    while(x) {
        if (x & 1) 
            s = (s * x) % n;

        x = (x >> 1);
        x = (x * x) % n;
    }
    return s;
}
int main () {
    // 18 ^ 49 mod 23
    std::cout << add(18, 49, 23) << '\n';
    return 0;
}
