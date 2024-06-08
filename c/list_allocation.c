#include <stdio.h>
#include <stdlib.h>

int main () {
   int n;
   printf("ENTER THE LEN: ");
   scanf("%d", &n);
   int *l = (int*) malloc(sizeof(int) * n);
   if (l == NULL) return -1;
   printf("ENTER NUMBERS:\n");
   for (int i = 0; i < n; i++){
      int j;
      scanf("%d", &j);
      l[i] = j;
   }
   for (int i = 0; i < n; i++){
      printf("%d ", l[i]);
   }
   putchar('\n');
   free(l);
   return 0;
}
