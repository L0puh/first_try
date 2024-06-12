#include <stdio.h>

unsigned replace_byte(unsigned orig, int pos, unsigned x){
   if (pos >= sizeof(orig)) return 0;
   return (orig&~(0xFF<<(8*pos))) | (x<<(8*pos));
}
int main() {
   unsigned res = replace_byte(0x12345678, 0, 0xAB);
   printf("%.8x\n", res);
   return 0;
}
