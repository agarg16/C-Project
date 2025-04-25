#include "directory.h"

// Returns the working directory
void printWorkingDirectory(int forTerminalInput);

// Changes the directory (CD Command)
void changeDirectory(char *input, directory *head);

// Starts a catnap timer for a user specified number of seconds
void catNapTimer(int seconds);

// Exits the terminal
void exitTerminal();