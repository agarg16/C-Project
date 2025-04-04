#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "argControl.h"

char *whiteSpace = " ";
short spaceLocation;

char *getFirstArg(char *input){
    char *firstArg = malloc(sizeof(char) * 32);

    if(!firstArg){
        fprintf(stderr, "Memory allocation error");
        exit(1);
    }

    //isolate the first argument
    spaceLocation = strcspn(input, whiteSpace);
    for(int i = 0; i < spaceLocation; i++){
        firstArg[i] = input[i];
    }
    firstArg[spaceLocation] = '\0';
    return firstArg;
}

char **separateArgs(char *input){
    char **args = malloc(sizeof(char*) * 32);
    short count = 0;
    char *arg;

    if(!args){
        fprintf(stderr, "Memory Allocation Error");
        exit(1);
    }
    arg = getFirstArg(input); //get first arg
    while(*arg != '\0'){
        args[count] = arg; 
        input += strlen(arg) + 1; //go past the arg and space character and set new starting point
        count++;
        arg = getFirstArg(input); //get the new first arg
    }
    args[count] = NULL;
    free(arg);
    return args;
}

//count how many args were entered
int getLengthArgs(char **args){
    int count = 0;
    while(args[count] != NULL){
        count++;
    }
    return count;
}

//free all heap
void freeArgs(char **args){
    int length = getLengthArgs(args);
    for(int i = 0; i < length; i++){
    free(args[i]);
    }
    free(args);
    args = NULL;
}
