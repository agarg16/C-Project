#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <unistd.h>
#include <signal.h>
#include <sys/wait.h>
#include <errno.h>
#include "fork.h"
#include "cmds.h"
#include "sigint.h"
#include "catart.h"

int main(int argc, char *cmd[]) {
//    signal(SIGINT, handle_sigint); // Set up signal handler for SIGINT (Ctrl+C)
    if (argc > 1 && strcmp(cmd[1], "run") == 0) { // Initial main function call
        
        char *opt_args[] = {cmd[0], cmd[2], NULL}; // pass only t or h options to getopt
        char ch = getopt(argc, opt_args, "th"); // Accepted characters of t for terminal and h for help

        char userRunCmd[strlen(cmd[1]) + 1];
        strcpy(userRunCmd, cmd[1]); // Gets the (potential) run command from the user
        userRunCmd[strlen(userRunCmd)] = '\0'; // Ensures terminating character in array

        if(strcmp(userRunCmd, "run") == 0 || strcmp(userRunCmd, "RUN") == 0 ) {
            if(ch == 't') {
                 printWorkingDirectory(1);
                 printf(" $ ");
                 char input[101];
                 input[strcspn(input, "\n")] = 0; // Remove trailing newline character from input
                 input[100] = '\0'; // Ensures terminating character in array
                 fgets(input, sizeof(input), stdin);
                 forkCMDs(input); // Forks to re-run main function with the desired command
            }
            else if(ch == 'h') {
                printf("List of Initial Command Options:\n");
                printf(" - ./main run -t: Starts the basic CLI terminal for user-entered commands\n");
                printf(" - ./main run -h: Provides a list of options running that the ./main program allows\n");
                
                printf("List of Terminal Command Options:\n");
                printf(" - cd:   Change the current working directory\n");
                printf(" - pwd:  Print the current working directory\n");
                printf(" - catnap: Start a timer for a user-specified number of seconds\n");
                printf(" - exit: Exit the program\n");
                
                return 0;
            }
            else {
                fprintf(stderr, "You have entered an invalid option. If you need help on accepted options, type \"./main run -h\" for initial and terminal command options.\n");
                return 1;
            }
        }
        else { 
            fprintf(stderr, "You have entered an invalid command. If you need help on accepted commands, type \"./main run -h\" for initial and terminal command options.\n");
            return 1;
        }
    }
    else if(argc > 1 && strcmp(cmd[1], "run") != 0) { // Not the initial main call
        char commandName[strlen(cmd[1]) + 1];
        strcpy(commandName, cmd[1]);
        commandName[strlen(commandName)] = '\0';

        if(strstr(commandName, "pwd") != NULL) {
            printWorkingDirectory(0);
            printf("\n");
            return 0;
        }
        else if(strcmp(commandName, "cd") == 0) {
            char *curPath = cmd[2];
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

            changeDirectory(curPath, head);

            freeDirectory(head, tail); // Frees the directory linked list

            char *args[] = {"./main", "run", "-t", NULL};
            if(execvp(args[0], args) == -1) {
                fprintf(stderr, "%s\n", strerror(errno));
            }
        }
        else if(strstr(commandName, "catnap") != NULL) {
            int seconds = 0;
            catNapTimer(seconds); // Starts the catnap timer with user input
        }
        else if(strstr(commandName, "exit") != NULL) {
            printf("Exiting...\n");
            exitTerminal();
            return 0;
        }
        else {
            fprintf(stderr, "Invalid command entered.\n");
            return 1;
        }
    }
    else { // Error
        fprintf(stderr, "Too few arguments entered. Please type \"./main run -h\" for initial and terminal command options.\n");
        return 1;
    }

    return 0;
}