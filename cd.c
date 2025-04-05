#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <unistd.h>

int main(int argc, char *argv[]) {
   int numForwardSlashes = 0;
   int lastSlash = 0;
   if(argc > 2) {
      char *startingChar = argv[2];

      for(int  i = 0; i < strlen(argv[2]); i++) {
         if(argv[2][i] == '/') {
            char *word = malloc(sizeof(argv[2]));
            strncpy(word, startingChar, &argv[2][i] - startingChar);
            printf("%s\n", word);
            startingChar = &(argv[2][i + 1]);
            lastSlash = i + 1;
            numForwardSlashes++;
         }
      }
   }
   else {
      fprintf(stderr, "Not enough arguments for %s", argv[1]);
   }

   return 0;
}
