#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <unistd.h>
#include "cmds.h"
#include "sigint.h"
#include "catart.h"
#include "tabcomp.h"

void printWorkingDirectory(int forTerminalInput) {
  if(getenv("USER_DIRECTORY") != NULL) { // if the user directory exists
      if(forTerminalInput == 1 && (strlen(getenv("USER_DIRECTORY")) > strlen(getenv("HOME")))) { // if current working directory is inside $HOME
        printf("~"); // 
        printf("%s", getenv("USER_DIRECTORY") + strlen(getenv("HOME"))); // prints the current working directory relative to $HOME (~)
      }
      else { printf("%s", getenv("USER_DIRECTORY")); } // if not inside $HOME, print full path
  }
  else {
      if(forTerminalInput == 1 && (strlen(getenv("PWD")) > strlen(getenv("HOME")))) { // if current working directory is inside $HOME using PWD
        printf("~"); 
        printf("%s", getenv("PWD") + strlen(getenv("HOME")));
      }
      else {
        printf("%s", getenv("PWD")); // if not inside $HOME, print full user path
      }
  }
}

void changeDirectory(char *input, directory *head) {
  int numForwardSlashes = 0; // counts number of forward slashes in the input
  int lastSlash = 0; // keeps track of the last forward slash in the input
  char word[strlen(input) + 1];
  strcpy(word, input); // copy input to new string
  word[strlen(input)] = '\0'; // adds terminating character to the end of string


  if(input[strlen(input) - 1] == '/') { // if the user input ends with a forward slash
    word[strlen(word) - 1] = '\0'; // removes the extra forward slash at the end
    setenv("USER_DIRECTORY", word, 1); // updates path formatting and updates USER_DIRECTORY environment 
  }
  else {
    setenv("USER_DIRECTORY", word, 1); 
  }

  char *startWord = getenv("PWD");
  char *endWord = startWord + 1;
  directory *tempHead = head;
  directory *nextPtr = tempHead;
  // linked list traversal setup

  for(directory *i = head; i != NULL && endWord != NULL; i = i->nextPartOfDir) { // actual traversal of linked list
    startWord = endWord; 
    endWord = strchr(endWord, '/'); // find next forward slash in input 
    
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
    tempHead->nextPartOfDir->isPartOfWorkingDir = 0; // last node in the linked list is not part of the working directory
  }

  char newEnvVarName[strlen(input) + 1];
  strcpy(newEnvVarName, "");
  // build new environment variable name

  for(directory *ptr = head; ptr != NULL && ptr->isPartOfWorkingDir == 1; ptr = ptr->nextPartOfDir) { /* declare ptr to traverse, condition is that ptr is not NULL and 
    is part of the working directory, set ptr to next part of directory */ 
    strcat(newEnvVarName, "/"); // add forwards slash before each name in directory
    strcat(newEnvVarName, ptr->name); // add(append) name of directory to new environment variable name
  }
  
  setenv("USER_DIRECTORY", newEnvVarName, 1); // update environment variable with new path
}

void catNapTimer(int seconds) { // signal interrupt testing
  char input[5]; // buffer for user input
  printf("Cat Nap Timer!\n");
  printf("Enter the number of seconds for the cat to nap: ");
  disableRawMode(); // Disable raw mode to allow for normal input handling
  do {
      fgets(input, sizeof(input), stdin); // Read user input for seconds
      seconds = atoi(input); // Convert input string to integer
      
      if (seconds <= 0) {
          printf("Invalid number of seconds. Please enter a positive integer.\n");
          printf("$ "); 
      }
  } while (seconds <= 0); // Loop until a valid positive integer is entered

  enableRawMode(); // Re-enable raw mode after input is read

  printf("\nCat is now snoozing... \n");
  catAsleep(); // Call the cat art function to show the cat asleep
  fflush(stdout); // Ensure the output is printed immediately

  for (int i = seconds; i > 0; i--) {
      printf("\rTime left: %d seconds\n", i); // Print countdown (/r moves cursor back to beginning of the line)
      if (i == 1) {
          printf("\rTime left: %d second\n", i); // Special case for singular second
      }
      fflush(stdout); // Ensure the countdown is printed immediately
      sleep(1); // Sleep for user specified time in seconds
  }
  catAwake(); // Call the cat art function to show the cat awake
  printf("\nCat is done napping\n");
}

// Exits the terminal
void exitTerminal() { exit(1); }