#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "directory.h"
#include "pwd.h"

// Prints out the working directory
void printWorkingDirectory(directory *startingLocation) {
   for(directory *head = startingLocation; head != NULL && head->isPartOfWorkingDir == 1; head = head->nextPartOfDir) {
       printf("/%s", head->name);
   }
 
   printf("\n");
}
