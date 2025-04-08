#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "pwd.h"

// Prints out the working directory
void printWorkingDirectory(directory *startingLocation) {
   for(directory *head = startingLocation; head != NULL && head->isPartOfWorkingDir == 1; head = head->nextPartOfDir) {
      if(head->isPartOfWorkingDir == 1) {
         printf("/%s", head->name);
      }
   }
   printf("\n");
}

// Creates a directory node
void createDirectoryNode(directory **ptrToHead, directory **ptrToTail, char *n) {
   directory *newDirNode = malloc(sizeof(directory));
   strcpy(newDirNode->name, n);
   newDirNode->isPartOfWorkingDir = 0;
   newDirNode->prevPartOfDir = *ptrToTail;
   newDirNode->nextPartOfDir = NULL;
   newDirNode->prevPartOfDir->nextPartOfDir = newDirNode;
   *ptrToTail = newDirNode;
}

// Frees linked list allocated memory
void freeDirectory(directory *head, directory *tail) {
   directory *temp = NULL;

   while(head != NULL) {
      temp = head->nextPartOfDir;
      free(head);
      head = temp;
   }
   tail = NULL;
   free(tail);
}
