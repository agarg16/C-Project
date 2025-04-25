#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <errno.h>
#include <signal.h>
#include <sys/wait.h>
#include "catart.h"

void handle_sigint(int sig) {
    printf("\n Process interrupted (Ctrl+C), Returning to terminal.\n");
    fflush(stdout);
//     char *args[] = { "./main", "run", "-t", NULL }; // Arguments to re-run the terminal command (simulates typing "./main run -t" again)
//     execvp(args[0], args); // execvp replaces the current process image with a new process image (restarts terminal shell)

//     // if execvp fails
//     fprintf(stderr, "Failed to restart terminal: %s\n", strerror(errno));
//     exit (1);
}

