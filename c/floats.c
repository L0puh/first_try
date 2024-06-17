#include <limits.h>
#include <stdio.h>

void print_bit(float a, size_t size);

int main(){
   float a = -3.2;
   print_bit(a, sizeof(float));
   return 0;
}

void print_bit(float a, size_t size){
   unsigned int b = *((unsigned int*)&a);
   size_t sz = size * CHAR_BIT;
   sz = (size * CHAR_BIT)-1;
   printf("%d | ", ((b>>sz) & 0x1));
   while(sz--){
      if (sz == (size*CHAR_BIT)-8) printf(" | ");
      printf("%d ", ((b>>sz) & 0x1));
   }
   putchar('\n');
}
