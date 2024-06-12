#include <stdio.h>

int is_little_endian(){
   int a = 1;
   char* addr = (char*) &a;
   if ((int)addr[0] == 1) printf("big endian: 0x "); 
   else printf("little endian: 0x ");
   for (int i = 0; i < sizeof(int); i++){
      printf("%.2x ", addr[i]);
   }
   putchar('\n');
   return 0;
}


int main() {
   is_little_endian();
   return 0;
}
