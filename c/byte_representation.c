/*************************
 *      PLAYGROUND       *
 *   WITH BYTES && BITS  *
 ************************/

#include <stdio.h>

void print_bit(unsigned int a, size_t size);

// without using == and !=
int any_eq_one(unsigned x, size_t w){
   for (int i = 0; i < w; i++)
      return((x>>i) & 1);
   return 0;
}

int any_eq_zero(unsigned x, size_t w){
   for (int i = 0; i < w; i++)
      return (((x>>i)&1) ^ 1);
   return 0;
}

int any_odd_one(unsigned x){
   for (int i = 1; i < sizeof(x); i+=2)
      if (x >> i == 1) return 1;
   return 0;
}

/* for little endian: */
int any_least_eq_one(unsigned x, size_t w){
   return x << ((w-1)<<3);
}
int any_most_eq_zero(unsigned x, size_t w){
   return (x & 1) ^ 1;
}

int int_shifts_are_arithmetic(){
   int a = 2<<3;
   printf("%lld\n", (long long)(1<<a));
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

   if(any_odd_one(2)) printf("ANY ODD IS ONE\n");
   if(any_eq_one (255, 32)) printf("ANY EQUALS 1\n");
   if(any_eq_zero(255, 32)) printf("ANY EQUALS 0\n");

   if(any_least_eq_one(255, sizeof(int))) printf("any least significant byte == 1\n");
   if(any_most_eq_zero(2,   sizeof(int))) printf("any most significant byte == 0\n");
   
   if(int_shifts_are_arithmetic()) printf("int shitfts are arithmetic\n");

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
