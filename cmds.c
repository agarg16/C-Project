#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "cmds.h"

void printWorkingDirectory() {
    if(getenv("USER_DIRECTORY") != NULL) {
        printf("%s", getenv("USER_DIRECTORY"));
    }
    else {
        printf("%s", getenv("PWD"));
    }
}

void changeDirectory(char *input, directory *head) {
    int numForwardSlashes = 0;
    int lastSlash = 0;
    char word[strlen(input) + 1];
    strcpy(word, input);
    word[strlen(input)] = '\0';

  
    if(input[strlen(input) - 1] == '/') {
      word[strlen(word) - 1] = '\0'; // Removes the extra forward slash at the end
      setenv("USER_DIRECTORY", word, 1);
    }
    else {
      setenv("USER_DIRECTORY", word, 1);
    }
  
    char *startWord = getenv("PWD");
    char *endWord = startWord + 1;
    directory *tempHead = head;
    directory *nextPtr = tempHead;

    for(directory *i = head; i != NULL && endWord != NULL; i = i->nextPartOfDir) {
      startWord = endWord;
      endWord = strchr(endWord, '/');
      
      // If there are still directory locations (separated by /) to get through
      if(endWord != NULL) {
        char shortenedWord[endWord - startWord + 1]; // Accommodates the '\0' character at the end
        shortenedWord[endWord - startWord] = '\0';
        strncpy(shortenedWord, startWord, endWord - startWord);
        startWord = endWord + 1;
        
        // Sets isPartOfWorkingDir to 1 if the directory location is included in the user's new requested directory (0 if not)
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
      else if(strcmp(tempHead->nextPartOfDir->name, startWord) == 0) { // If we are on the last directory location of the user-requested directory
          tempHead->nextPartOfDir->isPartOfWorkingDir = 1;
          break;
      }
    }
    
    if(tempHead->nextPartOfDir != NULL) {
      tempHead->nextPartOfDir->isPartOfWorkingDir = 0;
    }

    char *newEnvVarName = malloc(sizeof(input) + sizeof(char));
    for(directory *ptr = head; ptr != NULL  && ptr->isPartOfWorkingDir == 1; ptr = ptr->nextPartOfDir) {
        strcat(newEnvVarName, "/");
        strcat(newEnvVarName, ptr->name);
    }
    
    setenv("USER_DIRECTORY", newEnvVarName, 1);
}

// Exits the terminal
void exitTerminal() { exit(1); }
