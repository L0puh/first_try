#include <limits.h>
#include <stdio.h>

int uadd_ok(unsigned x, unsigned y){
   int res = x+y;
   return !(res < x || res < y);
}

int main(){
   if (uadd_ok(UINT_MAX, UINT_MAX)){
      printf("no overflow\n");
   } else 
      printf("overflow\n");
   return 0;
}

