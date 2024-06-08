#include <stdio.h>
#include <stdlib.h>

void swap(int *a, int *b){
   int tmp = *a;
   *a = *b;
   *b = tmp;
}

void sort(int *a, size_t size) {
   int min;
   for (int i = 0; i < size-1; i++){
      min = i; 
      for (int j = i+1; j < size; j++){
         if (a[j] < a[min]) min = j;
      }
      if (min != i) swap(&a[i], &a[min]);
   }
}

int main () {
   int n;
   printf("SIZE: ");
   scanf("%d", &n);
   int *l = (int*) malloc(sizeof(int) * n);
   if (l == NULL) return -1;
   printf("NUMBERS:\n");
   for (int i = 0; i < n; i++){
      int j;
      scanf("%d", &j);
      l[i] = j;
   }
   sort(l, n);
   for (int i = 0; i < n; i++){
      printf("%d ", l[i]);
   }
   putchar('\n');
   free(l);
   return 0;
}
