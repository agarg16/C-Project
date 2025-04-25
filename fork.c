#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include <stdlib.h>
#include <errno.h>
#include <sys/wait.h>
#include <signal.h>
#include "sigint.h"
#include "cmds.h"

// Forks the mock terminal to run commands in separate processes
void forkCMDs(char *input) {
    pid_t pid;
    pid_t wpid;

    pid = fork();
    if(pid == -1) { // Failed to Fork
        fprintf(stderr, "Error forking child process\n");
        return;
    }
    else if(pid == 0) { // Child Process
        char *inputIndex1;
        inputIndex1 = strchr(input, ' '); // Determines if cd with a directory location or only a single command with no additional arguments

        if(inputIndex1 == NULL) { // pwd or exit function
            char *args[] = { "./main", input, NULL };

            if(execvp(args[0], args) == -1) {
                fprintf(stderr, "%s\n", strerror(errno));
            }
        }
        else { // cd function
            char *firstWordStart = input;
            char *firstWord = malloc((inputIndex1 - firstWordStart) * sizeof(char *));
            strncpy(firstWord, firstWordStart, inputIndex1 - firstWordStart);

            firstWord[inputIndex1 - firstWord] = '\0'; // Ensures terminating character in array

            char *args[] = { "./main", firstWord, inputIndex1 + 1, "1", NULL };

            if(execvp(args[0], args) == -1) {
                fprintf(stderr, "%s\n", strerror(errno));
            }
        }
    }
    else { // Parent Process
       // signal(SIGINT, handle_sigint); // Set up signal handler for SIGINT (Ctrl+C)
        char word[strlen(input) + 1];
        strcpy(word, input);
        word[strlen(word) - 1] = '\0';

        int status = 0;
        wpid = wait(&status);

        // if(strcmp(word, "exit") != 0) {
        //     char *args[] = { "./main", "run", "-t", NULL };

        //     if(execvp(args[0], args) == -1) {
        //         fprintf(stderr, "%s\n", strerror(errno));
        //     }
        // }

        if (strcmp(word, "exit") != 0) {
            // Just reprint prompt instead of restarting main
            // printf("\n");
            // printWorkingDirectory(1);
            // printf(" $ ");
            // fflush(stdout);
        }     

    }
}