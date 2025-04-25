// Finds the entirety of the current argument
char *getFirstArg(char *input);

// Separate arguments from user input
char **separateArgs(char *input);

// Check if arg is a "built-in" command or not
int loopBuiltInCmds(char *arg);

// Count how many arguments were entered
int getLengthArgs(char **args);

// Free all of args heap
void freeArgs(char **args);