/*
    performs logic and 
    arithmetic right shift 
    of x by k (can be buggy)
*/

#include <stdio.h>

//TODO:
int logical(int x, int k){
   int res, w = 8*sizeof(int);
   if (k >= w || k < 0) return 0;
   res = (unsigned) x >> k;
   return res;
}

unsigned arithmetical(unsigned x, int k){
   unsigned res, w = 8 * sizeof(int);
   if (k >= w || k < 0) return 0;
   res = (int) x >> k;
   int msb = (x >> (sizeof(int)-1)<<3) & 0xFF;
   return res;
}

int main(){
   int orig = 0x00000010, k = 4;
   int x = logical(orig, k);
   unsigned y = arithmetical(orig, k); 
   printf("L: %.32x\nA: %.32x\n", x, y);
   return 0;
}
