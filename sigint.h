#ifndef SIGINT_H
#define SIGINT_H

/* SIGINT handled by replacing current process with a new version, ensuring the user stays within mock terminal but allowing them
   to enter a different command */
void handle_sigint(int sig);

#endif
