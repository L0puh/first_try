/**********************
 * program to examine 
 * disassembling and 
 * machine level code
 **********************/

#include <stdio.h>

void multstore(long, long, long*);

int main() {
   long d;
   multstore(2, 3, &d);
   printf("3 * 2 = %ld\n", d);
   return 0;
}

long mult2(long a, long b){
   long s = a * b;
   return s;
}
