#include <stdio.h>
#include <string.h>
#include <stdlib.h>

/* A directory location, including the name of the location, whether or not it is
   part of the working directory, and the next directory location it points to */
typedef struct directory {
   char name[20]; // Name of the current location
   unsigned int isPartOfWorkingDir: 1; // Whether or not this node is part of the working directory (0: no, 1: yes)
   struct directory *nextPartOfDir; // Pointer to the next directory node
   struct directory *prevPartOfDir; // Pointer to the previous directory node
} directory;

// Prints out the working directory
void printWorkingDirectory(directory *startingLocation) {
   for(directory *head = startingLocation; head != NULL && head->isPartOfWorkingDir == 1; head = head->nextPartOfDir) {
      if(head->isPartOfWorkingDir == 1) {
         printf("%s/", head->name);
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
}
