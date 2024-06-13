#include <stdio.h>

int is_little_endian(int a){
   char* addr = (char*) &a;
   for (int i = 0; i < sizeof(int); i++){
      printf("%.2x ", addr[i]);
   }
   if ((int)addr[0] == 1) printf("| big endian\n"); 
   else { 
      printf("| little endian\n");
      return 1;
   }
   putchar('\n');
   return 0;
}


