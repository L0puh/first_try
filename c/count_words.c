#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_STRING 10

int main (int argc, char* argv[]) {
   if (argc == 1) return -1;
   int current_max = MAX_STRING, 
       count = 0;
   char ch, *string;
   FILE *file;
   string = malloc(sizeof(char) * current_max);
   file = fopen(argv[1], "r");
   if (file == NULL || string == NULL) 
      return -1;
   do {
      ch = fgetc(file);
      string[count] = ch;
      count++;
      if (count >= current_max) {
         char *cp = malloc(sizeof(char)*count);
         strcpy(cp, string);
         current_max += MAX_STRING;
         string = malloc(sizeof(char)*current_max);
         strcpy(string, cp);
      }
   } while (ch != EOF);
   if (string[count-1] == EOF) count--;
   fclose(file);
   int words = 0, blank = 0, lines = 0;
   char prev;
   for (int i = 0; i < count; i++){
      if (string[i] == ' ') blank++;
      if (string[i] == '\n') lines++;
      if (prev != ' ' && prev != '\n' && (string[i] == ' ' || string[i] == '\n') ){
          words++;
      }

      prev = string[i];
   }
   printf("lines: %d  words: %d  blank :%d\nTOTAL:%d\n\n",
                     lines, words, blank, words+blank);
   
   for (int i = 0; i < count; i++){
      printf("%c", string[i]);
   }
   return 0;
}
