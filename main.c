#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <unistd.h>
#include "directory.h"
#include "pwd.h"
#include "cd.h"

int main(int argc, char *argv[]) {
   char ch = getopt(argc, argv, "h");

   // Create home directory node
   directory *home = malloc(sizeof(directory));
   strcpy(home->name, "home\0");
   home->isPartOfWorkingDir = 1;
   home->nextPartOfDir = NULL;
   home->prevPartOfDir = NULL;
   
   // Set environment variable representing the user's directory to default home location
   setenv("USER_DIRECTORY", "/home", 1);
   
   directory *head = home;
   directory *tail = head;

   // Creates all other nodes in the directory linked list
   createDirectoryNode(&head, &tail, "nextArea");
   createDirectoryNode(&head, &tail, "otherArea");
   createDirectoryNode(&head, &tail, "anotherOne");
   createDirectoryNode(&head, &tail, "lastOne");
   
   // If user types -h as an option, the help menu appears
   // Otherwise, command entered runs as expected
   if(ch == 'h') {
      printf("Help Command Options\n");
      printf(" - cd: Change the current working directory\n");
      printf(" - pwd: Print the current working directory\n");
      printf(" - exit: Exit the program\n");
   }
   else {
      if(argc > 1) {
        char command[strlen(argv[1])];
        strcpy(command, argv[1]);
        
        if(strcmp(command, "cd") == 0) { // The user uses the cd command
            changeDirectory(argc, argv, head);
            printWorkingDirectory();
         }
         else if(strcmp(command, "pwd") == 0) { // The user uses the pwd command
            printWorkingDirectory();
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
   
   return 0;
}
