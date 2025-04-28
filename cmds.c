#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <unistd.h>
#include <signal.h>
#include <sys/wait.h>
#include <errno.h>
#include "fork.h"
#include "cmds.h"
#include "sigint.h"
#include "catart.h"

// Prints the working directory
void printWorkingDirectory(int forTerminalInput) {
    if(forTerminalInput == 1 && (strlen(getenv("PWD")) > strlen(getenv("HOME")))) {
      printf("~");
      printf("%s", getenv("PWD") + strlen(getenv("HOME")));
    }
    else {
      printf("%s", getenv("PWD"));
    }
}

// Changes the directory
void changeDirectory(char *input, directory *head) {
    if(strlen(input) > 1 && input[strlen(input) - 1] == '/') {
      input[strlen(input) - 1] = '\0';
    }
    else {
      input[strlen(input)] = '\0';
    }
  
    char *startWord = input + 1;
    char *endWord = strchr(startWord, '/');
//    directory *tempHead = head;
    directory *nextPtr = head;

    for(directory *i = head; i != NULL; i = i->nextPartOfDir) {
      if(endWord != NULL) {
        char shortenedWord[endWord - startWord + 1]; // Accommodates the '\0' character at the end
        strncpy(shortenedWord, startWord, endWord - startWord);
        shortenedWord[endWord - startWord] = '\0';

        // Sets isPartOfWorkingDir to 1 if the directory location is included in the user's new requested directory (0 if not)
        for(nextPtr = i; nextPtr != NULL; nextPtr = nextPtr->nextPartOfDir) {
          // Whether or not the node name is the same as the specific directory location being looked at
          if(strcmp(nextPtr->name, shortenedWord) == 0) {
            nextPtr->isPartOfWorkingDir = 1;
          }
          else {
            nextPtr->isPartOfWorkingDir = 0;
          }
        }

        startWord = endWord + 1;
      }
      else {
        i->isPartOfWorkingDir = 1;
        break;
      }

      if(startWord != NULL) { endWord = strchr(startWord + 1, '/'); }
    }

      char newEnvVarName[strlen(input) + 1];
      strcpy(newEnvVarName, "");

      for(directory *ptr = head; ptr != NULL && ptr->isPartOfWorkingDir == 1; ptr = ptr->nextPartOfDir) {
        strcat(newEnvVarName, "/");
        strcat(newEnvVarName, ptr->name);
      }
      
      setenv("PWD", newEnvVarName, 1);
}

// Displays a cat nap timer
void catNapTimer(int seconds) { // signal interrupt testing
  char input[5]; // buffer for user input
  printf("Cat Nap Timer!\n");
  printf("Enter the number of seconds for the cat to nap: ");
  fgets(input, sizeof(input), stdin); // Read user input for seconds
  input[strcspn(input, "\n")] = '\0';  // remove newline
  seconds = atoi(input); // Convert input string to integer    
    if (seconds <= 0) {
      printf("Invalid number of seconds. Please enter a positive integer.\n");
      printf(" $ "); 
      return; // Exit the function if the input is invalid
    }

  printf("\nCat is now snoozing... \n");
  catAsleep(); // Call the cat art function to show the cat asleep
  fflush(stdout); // Ensure the output is printed immediately

  for (int i = seconds; i > 0; i--) {
      if(i > 1) {
        printf("\rTime left: %d seconds\n", i); // Print countdown (/r moves cursor back to beginning of the line)
      }
      else { // if (i == 1)
          printf("\rTime left: %d second\n", i); // Special case for singular second
      }
      fflush(stdout); // Ensure the countdown is printed immediately
      sleep(1); // Sleep for user specified time in seconds
  }
  catAwake(); // Call the cat art function to show the cat awake
  printf("\nCat is done napping...\n");
}

// Exits the terminal
void exitTerminal() { exit(0); }
