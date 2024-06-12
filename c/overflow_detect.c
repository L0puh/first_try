#include <limits.h>
#include <stdio.h>

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
   if (uadd_ok(10, 10) && tadd_ok(INT_MAX, -1)){
      printf("no overflow\n");
   } else 
      printf("overflow\n");
   return 0;
}

