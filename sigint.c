#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <errno.h>
#include <signal.h>
#include <sys/wait.h>
#include "cmds.h"

/* SIGINT handled by replacing current execvp with a new version,
   ensuring the user stays within mock terminal but allowing them
   to enter a different command */
void handle_sigint (int sig) {
   write(1, "\nSIGINT USED\n", sizeof("SIGINT USED\n"));
   // still need to write what we want to have happen during the counting file
}
