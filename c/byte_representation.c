/*************************
   little script to see 
   the format of endian.
 ************************/

#include <stdio.h>

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

void print_int(int x){
   print_bytes((unsigned char*) &x, sizeof(int));
}
void print_float(float x){
   print_bytes((unsigned char*) &x, sizeof(float));
}
void print_ptr(void* x){
   print_bytes((unsigned char*) &x, sizeof(void*));
}

int main() {
   short i = 12345;
   int number = 1;
   while (number > 0){
      scanf("%d", &number);
      print_bit(number, 10);
      printf("%d %u\n", number, (unsigned int)number);
   }
   /* print_bytes((unsigned char*)&i, sizeof(int)); */
   i = -i;
   /* print_bytes((unsigned char*)&i, sizeof(int)); */
   int x = 0x87654321;  
   int exp = 0xFF;
   /* printf("A: 0x%.8x\n", x & exp); */
   /* printf("B: 0x%.8x\n", x ^ ~exp); */
   /* printf("C: 0x%.8x\n", (x & ~(exp)) | exp); */
   /* printf("C: 0x%.8x\n", x | exp); */
   
   return 0;
}
