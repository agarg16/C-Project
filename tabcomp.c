#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <unistd.h>
#include <errno.h>
#include <termios.h>
#include "cmds.h"
#include "fork.h"

static struct termios originalTermios;


void disableRawMode(){
    tcsetattr(STDIN_FILENO, TCSAFLUSH, &originalTermios); // reads original keyboard settings before changing
    /*
    STDIN_FILENO - standard input file descriptor (usually 0)
    TCSAFLUSH - tells tcsetattr() when to apply changes and handle unread input
    &originalTermios - pointer to original termios to save original settings
    This function is called when the program exits to restore the terminal settings
    */
}
void enableRawMode(){
    tcgetattr(STDIN_FILENO, &originalTermios); 
    atexit(disableRawMode); // register disableRawMode to be called on exit

    struct termios raw = originalTermios;
    raw.c_lflag &= ~(ECHO | ICANON); // disable echo and canonical mode
    raw.c_cc[VMIN] = 1; // minimum number of characters to read
    raw.c_cc[VTIME] = 0; // no timeout for reading input

    tcsetattr(STDIN_FILENO, TCSAFLUSH, &raw); // apply new settings to terminal
}

void shellInputLoop() {
    enableRawMode();
    while(1){
        char input[101];
        input[100] = '\0'; // ensure null-termination of the string
        int length = 0;

        const char *cmds[] = {"cd", "pwd", "catnap", "exit", NULL};

        printWorkingDirectory(1); // print current working directory
        printf(" $ ");
        fflush(stdout);

        char c;
        while (read(STDIN_FILENO, &c, 1) == 1) {
            if (c == '\n') { // if user input is a newline (enter)
                input[length] = '\0'; // null-terminate the string
                printf("\n");
                forkCMDs(input); // execute the command
                break;
            }
            else if (c == '\t') { // if user input is tab
                int matchCount = 0; // count of matching commands
                const char *matchedCmd = NULL; // matched command initializer
                for (int i = 0; cmds[i] != NULL; i++) { // iterate through commands
                    if (strncmp(input, cmds[i], length) == 0) { // check if command starts with buffer
                        matchedCmd = cmds[i]; // store matched command 
                        matchCount++; // increment match count
                    }
                }
                if (matchCount == 1) {  // if one character matches, complete the command output
                    const char *remainder = matchedCmd + length; // get the remainder of the command
                    while (*remainder) { // print the remaining characters of the command}
                        input[length++] = *remainder; // add the remaining characters to the buffer
                        write(STDOUT_FILENO, remainder, 1); // write the remaining characters to standard output
                        remainder++; // move to next character
                    }
                }
                else if (matchCount > 1) {
                    printf("\nDid you mean one of these commands?\n");
                    for (int i = 0; cmds[i] != NULL; i++) { // iterate through commands
                        if (strncmp(input, cmds[i], length) == 0) { // compare and check if command starts with buffer
                            printf("%s\n", cmds[i]); // print the matching command
                        }
                        printf("\n$ %s", input); // print the buffer (user input)
                        fflush(stdout); // flush the output buffer
                    }
                }
            }
            else if (c == 127 || c == 8 || c == '\b') { // if user input is backspace
                if (length > 0){ // if buffer (user input) length is more than 0
                length--; // decrement the length of the buffer
                }
                printf("\b \b"); // print backspace, space, and backspace to remove the last character
                fflush(stdout); 
            }
            else {
                input[length++] = c; // add the character to the buffer
                write(STDOUT_FILENO, &c, 1); // write the character to standard output
            }
        }
    }
    disableRawMode(); // disable raw mode when done
}