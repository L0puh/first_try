#include <stdio.h>

int main() {
   union {
      short s;
      char  c[sizeof(short)];
   } un;
   un.s = 0x0102;   
   if (sizeof(short)==2){
      if (un.c[0] == 1 && un.c[1] == 2)
         printf("big endian: %x\n", un.s);
      else if (un.c[0] == 2 && un.c[1] == 1)
         printf("little endian: %x\n", un.s);
   }
   return 0;
}


