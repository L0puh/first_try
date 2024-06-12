/*************************
 *      PLAYGROUND       *
 *   WITH BYTES && BITS  *
 ************************/

#include <stdio.h>

void print_bit(unsigned int a, size_t size);

int any_odd_one(unsigned x){
   for (int i = 1; i < sizeof(x); i+=2)
      if (x >> i == 1) return 1;
   return 0;
}

void print_bit(unsigned int a, size_t size ){
    putchar('0');
    for (long i = 1 << size; i > 0; i = i / 2) {
        if ((a & i) != 0) putchar('1');
        else putchar('0');
    }
    putchar('\n');
}

void print_bytes(unsigned char* a, size_t size){
   printf("0x");
   for (int i = 0; i < size; i++) {
      printf("%.2x ", a[i]);
   }
   putchar('\n');
}

int main() {
   if(any_odd_one(4)) printf("ANY ODD ONE\n");
   int x = 0x89ABCDEF;
   int y = 0x76543210;
   printf("%x\n", (x&0xFF)|(y&~0xFF));
   
   short i = 12345;
   int number = 1;
   while (number > 0){
      scanf("%d", &number);
      print_bit(number, 10);
      printf("%d %u\n", number, (unsigned int)number);
   }
   
   return 0;
}
