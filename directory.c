#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <stdarg.h>
#include "directory.h"

// Creates a directory node
void createDirectoryNode(int argCount, ...) {
   directory *newDirNode = malloc(sizeof(directory));
   
   va_list list;
   va_start(list, argCount);
   
   input args;
   
   args.nodeName = va_arg(list, char *);
   strcpy(newDirNode->name, args.nodeName);
   
   args.curTail = va_arg(list, directory **);
   newDirNode->prevPartOfDir = *(args.curTail);
   newDirNode->nextPartOfDir = NULL;
   newDirNode->prevPartOfDir->nextPartOfDir = newDirNode;
   
   *args.curTail = newDirNode;
   
   args.workingDir = va_arg(list, int);
   newDirNode->isPartOfWorkingDir = args.workingDir;
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
