#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <unistd.h>
#include "directory.h"
#include "pwd.h"
#include "cd.h"

int main(int argc, char *argv[]) {
   char ch = getopt(argc, argv, "h");
   char *curPath = getenv("PWD"); // GETS THE CURRENT WORKING DIRECTORY (PWD for Ubuntu, PATH for Debian)
   printf("ACTUAL: %s\n", curPath);

   char *startWord = curPath;
   char *endWord = startWord + 1;
   char *word = malloc(sizeof(curPath));
   strcpy(word, "home"); // Initializes with a default home name for the directory
   
   endWord = strchr(endWord, '/');
   strncpy(word, startWord + 1, (endWord - startWord) - 1);

   // Create home directory node
   directory *home = malloc(sizeof(directory));
   strcpy(home->name, word);
   home->isPartOfWorkingDir = 1;
   home->nextPartOfDir = NULL;
   home->prevPartOfDir = NULL;
   
   directory *head = home;
   directory *tail = head;

   // Creates all other nodes in the directory linked list
   startWord = endWord + 1;
   endWord = strchr(startWord, '/');
   
   for(int i = 0; endWord != NULL && i < strlen(curPath); i++) {
      endWord = strchr(startWord, '/');
      
      if(endWord != NULL) {
          char shortenedWord[endWord - startWord + 1]; // Accommodates the '\0' character at the end
          shortenedWord[endWord - startWord] = '\0';
          strncpy(shortenedWord, startWord, endWord - startWord);
          startWord = endWord + 1;
          createDirectoryNode(3, shortenedWord, &tail, 1);
          //printf("%s\n\n", shortenedWord);
      }
      else {
          createDirectoryNode(3, startWord, &tail, 1);
          //printf("%s\n", startWord);
      }
   }
   
   setenv("USER_DIRECTORY", curPath, 1);
   
   // If user types -h as an option, the help menu appears
   // Otherwise, command entered runs as expected
   if(ch == 'h') {
      printf("Help Command Options\n");
      printf(" - cd:   Change the current working directory\n");
      printf(" - pwd:  Print the current working directory\n");
      printf(" - exit: Exit the program\n");
   }
   else {
      if(argc > 1) {
        char command[strlen(argv[1])];
        strcpy(command, argv[1]);
        
        if(strcmp(command, "cd") == 0) {         // The user uses the cd command
            changeDirectory(argc, argv, head);
            printf("CD DONE\n");
            printWorkingDirectory(head);
            printf("PWD AFTER CD DONE\n");
         }
         else if(strcmp(command, "pwd") == 0) {  // The user uses the pwd command
            printWorkingDirectory(home);
         }
         else if(strcmp(command, "exit") == 0) { // The user uses the exit command
            return 0;
         }
         else {
            fprintf(stderr, "Did not select valid command");
         }
       }
   }
   
   freeDirectory(head, tail);
   free(word);
   
   return 0;
}
