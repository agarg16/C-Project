#include <stdio.h>
#include <string.h>
#include <stdlib.h>

// A directory location, including the name of the location, whether or not it is part of the working directory, and the next directory location it points to
typedef struct directory {
    char name[20]; // Name of the current location
    unsigned int isPartOfWorkingDir: 1; // Whether or not this is part of the working directory (0 for no, 1 for yes)
    struct directory *nextPartOfDir; // Pointer to the next part of the directory
} directory;


// Prints out the working directory
void printWorkingDirectory (directory *startingLocation) {
    for(directory *head = startingLocation; head != NULL && head->isPartOfWorkingDir == 1; head = head->nextPartOfDir) {
        if(head->isPartOfWorkingDir == 1) {
            printf("%s\\", head->name);
        }
    }
}

int main() {
    char *userInput = malloc(50);

    directory *lastOne = malloc(sizeof(directory));
    strcpy(lastOne->name, "lastOne");
    lastOne->isPartOfWorkingDir = 0;
    lastOne->nextPartOfDir = NULL;

    directory *anotherOne = malloc(sizeof(directory));
    strcpy(anotherOne->name, "anotherOne");
    anotherOne->isPartOfWorkingDir = 0;
    anotherOne->nextPartOfDir = lastOne;

    directory *otherArea = malloc(sizeof(directory));
    strcpy(otherArea->name, "otherArea");
    otherArea->isPartOfWorkingDir = 0;
    otherArea->nextPartOfDir = anotherOne;

    directory *nextArea = malloc(sizeof(directory));
    strcpy(nextArea->name, "nextArea");
    nextArea->isPartOfWorkingDir = 0;
    nextArea->nextPartOfDir = otherArea;

    directory *home = malloc(sizeof(directory));
    strcpy(home->name, "home");
    home->isPartOfWorkingDir = 1;
    home->nextPartOfDir = nextArea;
    
    printf("Starting working directory:\n");
    printWorkingDirectory(home);

    nextArea->isPartOfWorkingDir = 1;
    printf("\n\nAfter adding on to the working directory:\n");
    printWorkingDirectory(home);

    nextArea->isPartOfWorkingDir = 0;
    otherArea->isPartOfWorkingDir = 1;
    printf("\n\nProof that it ends at the first instance of 0:\n");
    printWorkingDirectory(home);

    nextArea->isPartOfWorkingDir = 1;
    otherArea->isPartOfWorkingDir = 1;
    anotherOne->isPartOfWorkingDir = 1;
    lastOne->isPartOfWorkingDir = 1;
    printf("\n\nAll of them:\n");
    printWorkingDirectory(home);

    printf("\n\nStarting on otherArea:\n");
    printWorkingDirectory(otherArea);

    free(home);
    free(nextArea);
    free(otherArea);
    free(anotherOne);
    free(lastOne);

    return 0;
}