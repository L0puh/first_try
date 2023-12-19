/*
 * factorial of 5 is:
 * 5 = 5*4*3*2*1
 * this is a recursive function
 * implementing this thing
 */
#include <cstdio>
#include <iostream>

int factorial_r(int x){
    if (x == 1){
        return x;
    } else 
        return x * factorial_r(x-1);

}

int main() {
    int x;
    std::cin >> x;
    printf("x:%d, %d!:%d\n", x, x, factorial_r(x));

    return 0;
}
