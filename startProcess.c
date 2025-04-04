#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>
#include "argControl.h"
#include "startProcess.h"

void startProcess(char **args){
    pid_t pid;
    pid_t wpid;
    int status;
    
    
    pid = fork();
    if(pid == -1){ //failed to start child process
        fprintf(stderr, "Error forking child process\n");
    }
    else if(pid == 0){ //child process
        if(execvp(args[0], args) == -1){ //run new process
            fprintf(stderr, "command not found\n"); //if process not found or error kill child and free args
        }
        freeArgs(args);
        exit(1);
    }
    else{ //parent process
        wpid = wait(&status);
    }



}
