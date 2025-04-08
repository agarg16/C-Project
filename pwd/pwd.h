/* A directory location, including the name of the location, whether or not it is
   part of the working directory, and the next directory location it points to */
typedef struct directory {
   char name[20]; // Name of the current location
   unsigned int isPartOfWorkingDir: 1; // Whether or not this node is part of the working directory (0: no, 1: yes)
   struct directory *nextPartOfDir; // Pointer to the next directory node
   struct directory *prevPartOfDir; // Pointer to the previous directory node
} directory;

// Prints out the working directory
void printWorkingDirectory(directory *startingLocation);


// Creates a directory node
void createDirectoryNode(directory **ptrToHead, directory **ptrToTail, char *n);


// Frees linked list allocated memory
void freeDirectory(directory *head, directory *tail);
