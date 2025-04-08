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
   directory *head = malloc(sizeof(directory));
   strcpy(head->name, "home");
   head->isPartOfWorkingDir = 1;
   head->nextPartOfDir = NULL;
   head->prevPartOfDir = NULL;
   directory *tail = head;

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
      if(strcmp(argv[1], "cd") == 0) { // The user uses the cd command
          changeDirectory(argc, argv);
       }
       else if(strcmp(argv[1], "pwd") == 0) { // The user uses the pwd command
          printWorkingDirectory(head);
       }
       else if(strcmp(argv[1], "exit") == 0) { // The user uses the exit command
          return 0;
       }
       else {
          fprintf(stderr, "Did not select valid command");
       }
   }
   
   freeDirectory(head, tail);
   
   return 0;
}
