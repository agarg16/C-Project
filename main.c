#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <unistd.h>
#include <errno.h>
#include <signal.h>
#include <sys/wait.h>
#include "fork.h"
#include "cmds.h"
#include "sigint.h"
#include "argControl.h"
#include "catart.h"

int main(int argc, char *cmd[]) {
    signal(SIGINT, handle_sigint); // Set up signal handler for SIGINT (Ctrl+C)

    char *curPath = getenv("PWD");
    char *startWord = curPath;
    char *endWord = startWord + 1;
    char word[strlen(curPath)];
    
    strcpy(word, "home"); // Initializes with a default home name for the directory
    
    endWord = strchr(endWord, '/');
    strncpy(word, startWord + 1, (endWord - startWord) - 1);

    // Create home directory node
    directory *home = malloc(sizeof(directory));
    strcpy(home->name, word);
    home->isPartOfWorkingDir = 1;
    home->nextPartOfDir = NULL;
    home->prevPartOfDir = NULL;
    
    directory *head = home;
    directory *tail = head;

    // Creates all other nodes in the directory linked list
    startWord = endWord + 1;
    endWord = strchr(startWord, '/');
    
    for(int i = 0; endWord != NULL && i < strlen(curPath); i++) {
        endWord = strchr(startWord, '/');
        
        if(endWord != NULL) {
            char shortenedWord[endWord - startWord + 1]; // Accommodates the '\0' character at the end
            shortenedWord[endWord - startWord] = '\0';
            strncpy(shortenedWord, startWord, endWord - startWord);
            startWord = endWord + 1;
            createDirectoryNode(3, shortenedWord, &tail, 1);
        }
        else {
            createDirectoryNode(3, startWord, &tail, 1);
        }
    }

    // Whether or not the user entered more than just the execution file name upon first running the program
    if(argc > 1) {
        char ch = getopt(argc, cmd, "th"); // Accepted characters of t for terminal and h for help

        // Determines whether the user wanted to view the help list, wanted to start the terminal, or did not type in a valid option
        switch (ch) {
            case 't':
                while(1) {
                    // Terminal Input Line Formatting
                    printWorkingDirectory(1);
                    printf("$ ");

                    // Wait for user input
                    char input[200];
                    fgets(input, sizeof(input), stdin);

                    // Ensures there is no segmentation fault if the user only presses enter
                    if(input == NULL || strcmp(input, (char*)("\n")) == 0) { continue; }

                    input[strcspn(input, "\n")] = '\0'; // Removes newline character
                    char **args = separateArgs(input); // Separate the arguments from user input

                    // Whether or not a non-implemented (non-"built-in") command used
                    if(strlen(input) > 0 && loopBuiltInCmds(args[0]) == 0) {
                        forkCMDs(args);
                    }
                    else {
                        if(strcmp(args[0], "pwd") == 0) {
                            printWorkingDirectory(0);
                            printf("\n");
                        }
                        else if(strcmp(args[0], "cd") == 0) {
                            changeDirectory(args[1], head);
                        }
                        else if(strcmp(args[0], "exit") == 0) {
                            printf("Exiting...\n");
                            freeDirectory(head, tail); // Frees the directory linked list
                            freeArgs(args);
                            exitTerminal();
                        }
                        else if(strcmp(args[0], "catnap") == 0) {
                            int seconds = 0;
                            catNapTimer(seconds); // Starts the catnap timer with user input
                        }
                        else {
                            fprintf(stderr, "Error: invalid command entered\n");
                        }
                    }
                    freeArgs(args);
                }
                break;
            case 'h':
                printf("List of Initial Command Options:\n");
                printf(" - ./main run -t: Starts the basic CLI terminal for user-entered commands\n");
                printf(" - ./main run -h: Provides a list of options running that the ./main program allows\n");
                
                printf("List of Terminal Command Options:\n");
                printf(" - cd:   Change the current working directory\n");
                printf(" - pwd:  Print the current working directory\n");
                printf(" - catnap: Start a timer for a user-specified number of seconds\n");
                printf(" - exit: Exit the program\n");
                break;
            default:
                fprintf(stderr, "Error: invalid option selected. Please type \"./main run -h\" for initial and terminal command options.\n");
        }
    }
    else { // Not enough arguments to run the mock terminal
        fprintf(stderr, "Too few arguments entered. Please type \"./main run -h\" for initial and terminal command options.\n");
        return 1;
    }

    freeDirectory(head, tail); // Frees the directory linked list

    return 0;
}
