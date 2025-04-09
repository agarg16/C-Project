#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "directory.h"
#include "pwd.h"

// Prints out the working directory
void printWorkingDirectory(void) { printf("%s\n", getenv("USER_DIRECTORY")); }

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
}
