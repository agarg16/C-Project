#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include <stdlib.h>
#include <errno.h>
#include <sys/wait.h>
#include "argControl.h"

// Forks the mock terminal to run commands in separate processes
void forkCMDs(char **input) {
    pid_t pid;
    pid_t wpid;

    pid = fork();
    if(pid == -1) { // Failed to Fork
        fprintf(stderr, "Error forking child process\n");
        return;
    }
    else if(pid == 0) { // Child Process
        if(execvp(input[0], input) == -1){ //run new process
            fprintf(stderr, "Error: %s\n", strerror(errno)); //if process not found or error
        }
    }
    else { // Parent Process
        int status = 0;
        wpid = wait(&status);
    }
}
