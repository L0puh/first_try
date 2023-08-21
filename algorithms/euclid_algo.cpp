#include <cstdio>
#include <iostream>

int gcd(int x, int y) {
    int g;
    while (x > 0) {
        g = x;
        x = y % x;
        y = g;
        if (y == 1) return 1;
    }
    return g;
}

int main () {
    int x, y;
    std::cin >> x >> y;
    std::cout << gcd(x, y) << std::endl;
    return 0;
}
