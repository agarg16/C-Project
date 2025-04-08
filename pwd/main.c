#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "pwd.h"

int main(void) {
   char *userInput = malloc(50);

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

   printWorkingDirectory(head);

   freeDirectory(head, tail);

   return 0;
}
