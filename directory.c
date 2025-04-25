#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <stdarg.h>
#include "directory.h"

// Creates a directory node
void createDirectoryNode(int argCount, ...) {
   directory *newDirNode = malloc(sizeof(directory)); // allocate memory
   
   va_list list; // handle variable arguments
   va_start(list, argCount); // initalize variable argument list
   
   input args;
   
   args.nodeName = va_arg(list, char *); // gets name of directory node
   strcpy(newDirNode->name, args.nodeName); // copies name to new node
   
   args.curTail = va_arg(list, directory **); // current tail in the linked list
   newDirNode->prevPartOfDir = *(args.curTail); // sets previous node to current tail
   newDirNode->nextPartOfDir = NULL; // sets next node to NULL
   newDirNode->prevPartOfDir->nextPartOfDir = newDirNode; // sets current tail's next node to new node (i think)
   
   *args.curTail = newDirNode; // sets current tail to new node
   
   args.workingDir = va_arg(list, int); // working directory
   newDirNode->isPartOfWorkingDir = args.workingDir; // sets isPartOfWorkingDir to 1 if it is part of the working directory, 0 otherwise
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
