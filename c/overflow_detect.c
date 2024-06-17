#include <limits.h>
#include <stdio.h>

int tmul_ok64(int x, int y){ //using cast
   long r = (long)x*y;
   return r == (int)r;
}

int tmul_ok(int x, int y){
   int res = x*y;
   if (x == 0 && res == 0) return 1;
   return res/x == y;
}

int uadd_ok(unsigned x, unsigned y){
   int res = x+y;
   return res >= x && res >= y;
}

int tadd_ok(int x, int y){
   int res = x+y;
   int negative = x < 0  && y < 0 && res >= 0;
   int positive = x >= 0 && y >= 0 && res < 0;
   return !negative && !positive;
}

int main(){
   if (uadd_ok(10, 10) && tadd_ok(INT_MAX, -1) && tmul_ok64(INT_MAX, INT_MAX)){
      printf("no overflow\n");
   } else 
      printf("overflow\n");
   return 0;
}

