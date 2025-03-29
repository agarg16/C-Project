#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "getFirstArg.h"

char *getFirstArg(char *input){
    char *whiteSpace = " ";
    short spaceLocation;
    char *firstArg = malloc(sizeof(char) * 32);

    //isolate the first argument
    spaceLocation = strcspn(input, whiteSpace);
    for(int i = 0; i < spaceLocation; i++){
        firstArg[i] = input[i];
    }
    firstArg[spaceLocation] = '\0';
    return firstArg;
}
