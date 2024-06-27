#include <stdio.h>
#include <stdlib.h>

/*    Euclidean algorithm    */
int gcd(int a, int b){
   int rem, max = a, min = b;
   if (b > a) { max = b; min = a; }
   rem = min;
   while (rem > 0 ){
      printf("%d/%d=%d\n", max, rem, max%rem);
      rem = max%rem;
      max = min;
      min = rem;
   }
   return max;
}

int main(int argc, char* argv[]) {
   int a, b;
   if (argc != 3) 
      a = 1785, 
      b = 546;
   else  
      a = atoi(argv[1]), 
      b = atoi(argv[2]); 

   printf("GCD OF %d AND %d: %d\n", a, b,  gcd(a, b));
}
