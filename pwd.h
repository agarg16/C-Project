// Prints out the working directory
void printWorkingDirectory(directory *startingLocation);


// Creates a directory node
void createDirectoryNode(directory **ptrToHead, directory **ptrToTail, char *n);


// Frees linked list allocated memory
void freeDirectory(directory *head, directory *tail);
