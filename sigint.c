#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <errno.h>
#include <signal.h>
#include <sys/wait.h>

/* SIGINT handled by replacing current execvp with a new version,
   ensuring the user stays within mock terminal but allowing them
   to enter a different command */
void handle_sigint (int sig) {
    printf("\n");
   
    char *args[] = { "./main", "run", "-t", NULL };
    if(execvp(args[0], args) == -1) {
        fprintf(stderr, "%s\n", strerror(errno));
    }

    printf("SIGINT\n");
}
