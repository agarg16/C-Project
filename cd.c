#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <unistd.h>
#include "directory.h"

void changeDirectory(int argc, char *argv[], directory *head) {
   int numForwardSlashes = 0;
   int lastSlash = 0;
   
   // Ensures user entered enough arguments to provide a directory
   if(argc > 2) {
      char *startingChar = argv[2];

      // Iterates through every character in the full directory the user provides
      for(int  i = 0; i < strlen(argv[2]); i++) {
         /* If the entirety of a directory location name's characters has been read (since
         separated by '/' characters, allowing for user to not enter '/' for final location) */
         if(argv[2][i] == '/' || (i == strlen(argv[2]) - 1)) {
            lastSlash = i + 1;
            numForwardSlashes++;
            
            char *word = malloc(sizeof(argv[2]));
            if(argv[2][i] == '/') { 
              strncpy(word, startingChar, &argv[2][i] - startingChar);
            }
            else { // argv[2][i] == last character of directory location
              strncpy(word, startingChar, &argv[2][i] - startingChar + 1);
            }
            
            // If the first directory location is not home, exit function
            if(strcmp(head->name, word) != 0 && numForwardSlashes == 1) { 
              fprintf(stderr, "Invalid default directory location. Setting directory to: /%s\n", head->name);
              return;
            }
            
            /* Finds the matching node name to the current word and sets isPartOfWorkingDir to true
              (home node always true) */
            for(directory *nextPtr = head; nextPtr != NULL; nextPtr = nextPtr->nextPartOfDir) {
              if(strcmp(nextPtr->name, word) == 0) {
                nextPtr->isPartOfWorkingDir = 1;
              }
            }
            
            /* Repeats process with the next directory location by changing the starting
            character to the start of the new directory location */
            startingChar = &(argv[2][i + 1]);
         }
      }
   }
   else {
      fprintf(stderr, "Not enough arguments for %s", argv[1]);
   }
}
