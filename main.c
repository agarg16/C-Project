#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include "builtInCmds.h"

int main(int argc, char *argv[]) {
  // Flush after every printf
  setbuf(stdout, NULL);


  while (1) {
    printf("$ ");

    // Wait for user input
    char input[100];
    if(fgets(input, sizeof(input), stdin) == NULL){
    break;
    }

    input[strcspn(input, "\n")] = '\0'; // removes newline character (KEEP ABOVE COMMANDS)

    // echo command
    if (strncmp (input, "echo", strlen("echo")) == 0) { // echo command
      handle_echo(input);
      continue;
    } else if(strlen(input) == 0) { // if user simply presses enter
      continue;
    }


    // exit command
    if (strcmp(input, "exit") == 0 || strcmp(input, "exit 0") == 0) { // exit command
      handle_exit(input);
      continue;
    }

    // type command 
    if (strncmp(input, "type ", 5) == 0) { // checks if input starts with "type"
      char *arg = input + 5; // get argument after "type "
      handle_type(arg);
      continue;
    } 

    // pwd command
    if (strncmp(input, "pwd", strlen("pwd")) == 0) { //checks if input starts with "pwd"
      handle_pwd();
      continue;
    }

    // cd command
    if(strncmp(input, "cd", strlen("cd")) == 0) { //checks if input starts with "cd"
      handle_cd(input);
      continue;
    }
  

    printf("%s: command not found\n", input);

  }

  return 0;
  
}
