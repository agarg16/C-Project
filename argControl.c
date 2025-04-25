#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include <stdlib.h>

// Finds the entirety of the current argument
char *getFirstArg(char *input) {
    char *firstArg = malloc(sizeof(char) * 100);

    if(!firstArg){
        fprintf(stderr, "Memory allocation error");
        exit(1);
    }

    // Isolate the first argument
    int spaceLength = strcspn(input, " ");
    for(int i = 0; i < spaceLength; i++){
        firstArg[i] = input[i];
    }
    firstArg[spaceLength] = '\0';

    return firstArg;
}

// Separate arguments from user input
char **separateArgs(char *input) {
    char **args = malloc(32 * sizeof(char*));
    short count = 0;
    char *arg;

    if(!args){
        fprintf(stderr, "Memory Allocation Error");
        exit(1);
    }

    arg = getFirstArg(input); // Get first argument

    // Ensures no newline character saved in char array
    char *newlinePtr = strchr(arg, '\n');
    if(newlinePtr != NULL) { arg[newlinePtr - arg] = '\0'; }

    while(*arg != '\0'){
        args[count] = arg; 
        input += strlen(arg) + 1; //go past the arg and space character and set new starting point
        count++;
        arg = getFirstArg(input); //get the new first arg

        // Ensures no newline character saved in char array
        char *newlinePtr = strchr(arg, '\n');
        if(newlinePtr != NULL) { arg[newlinePtr - arg] = '\0'; }
    }
    
    args[count] = NULL;
    free(arg);

    return args;
}

// Check if arg is a "built-in" command or not
int loopBuiltInCmds(char *arg) {
    char *builtInList[] = { "exit", "pwd", "cd" };
    const int builtInListSize = sizeof(builtInList) / sizeof(char *);

    // Ensures no newline character saved in char array
    if(strchr(arg, '\n') != NULL) { arg[strcspn(arg, "\n")] = '\0'; }

    for(int i = 0; i < builtInListSize; i++) {
      if(strcmp(arg, builtInList[i]) == 0){
        return 1; // Built-in command found
      }
    }

    return 0; // Built-in command not found
}

// Count how many arguments were entered
int getLengthArgs(char **args){
    int count = 0;

    while(args[count] != NULL) { count++; }

    return count;
}

// Free all of args heap
void freeArgs(char **args){
    int length = getLengthArgs(args);
    for(int i = 0; i < length; i++){
    free(args[i]);
    }
    free(args);
    args = NULL;
}