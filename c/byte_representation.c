/*************************
   little script to see 
   the format of endian.
 ************************/

#include <stdio.h>

void print_bytes(unsigned char* a, size_t size){
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
   int a=0x12345678;
   print_bytes((unsigned char *)&a, 1);
   print_bytes((unsigned char *)&a, 2);
   print_bytes((unsigned char *)&a, 3);

   print_int(a);
   print_float((float)a);
   float b = 10.0f;
   print_float((float)b);
   print_ptr(&a);

   return 0;
}
