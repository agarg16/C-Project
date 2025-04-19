#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <unistd.h>
#include "directory.h"

void changeDirectory(int argc, char *argv[], directory *head) {
  int numForwardSlashes = 0;
  int lastSlash = 0;
  char word[strlen(argv[2]) + 1];
  strcpy(word, argv[2]);
  word[strlen(argv[2])] = '\0';

  if(strlen(word) > 0) {
    if(argv[2][strlen(argv[2]) - 1] == '/') {
      word[strlen(word) - 1] = '\0'; // Removes the extra forward slash at the end
      setenv("USER_DIRECTORY", word, 1);
    }
    else {
      setenv("USER_DIRECTORY", word, 1);
    }
  
    char *startWord = word;
    char *endWord = startWord + 1;
    directory *tempHead = head;
    directory *nextPtr = tempHead;

    for(directory *i = head; i != NULL && endWord != NULL; i = i->nextPartOfDir) {
      startWord = endWord;
      endWord = strchr(endWord, '/');
      
      if(endWord != NULL) {
        char shortenedWord[endWord - startWord + 1]; // Accommodates the '\0' character at the end
        shortenedWord[endWord - startWord] = '\0';
        strncpy(shortenedWord, startWord, endWord - startWord);
        startWord = endWord + 1;
        
        for(nextPtr = i; nextPtr != NULL; nextPtr = nextPtr->nextPartOfDir) {
          if(strcmp(nextPtr->name, shortenedWord) == 0) { // The node name is the same as the specific directory location being looked at
            nextPtr->isPartOfWorkingDir = 1;
            tempHead = nextPtr;
          }
          else {
            nextPtr->isPartOfWorkingDir = 0;
          }
        }
        endWord = endWord + 1;
      }
      else if(strcmp(tempHead->nextPartOfDir->name, startWord) == 0) {
          tempHead->nextPartOfDir->isPartOfWorkingDir = 1;
          return;
      }
    }
    
    if(tempHead->nextPartOfDir != NULL) {
      tempHead->nextPartOfDir->isPartOfWorkingDir = 0;
    }
  }
  else {
    fprintf(stderr, "Not enough arguments for %s\n", argv[1]);
  }
}
