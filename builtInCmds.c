#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include "builtInCmds.h"

void handle_echo (const char *input) {
    const char *message = input + strlen("echo"); // gets everything after "echo"
    
    while (*message == ' ') { // checks if there's a space after echo
      message++; // skips space in char array after "echo"
    }
    printf("%s\n", message); // prints rest of the input after skipping space
  
  }
  
  void handle_exit (const char *input) {
    exit(0); // exits program
  }
  
  void handle_type (const char *arg) {
    if (strcmp(arg, "echo") == 0) { // check if argument is "echo"
      printf("echo is a shell builtin\n");
    } else if (strcmp(arg, "exit") == 0) { // check if argument is "exit"
      printf("exit is a shell builtin\n");
    } else if (strcmp(arg, "type") == 0) { // check if argument is "type"
      printf("type is a shell builtin\n"); 
    } else if (strcmp(arg, "cd") == 0) { // check if argument is "cd"
      printf("cd is a shell builtin\n");
    }else if (strcmp(arg, "pwd") == 0) { // check if argument is "pwd"
      printf("pwd is a shell builtin");
    }else {
      printf("%s: not found\n", arg);
    }
  }
  
  void handle_path (const char *arg) {
    const char *name = "PATH"; // name of environment variable
    const char *env_p = getenv(name); // gets value of environment variable
    if (env_p == NULL) {
      printf("%s: not set\n", name); 
    }
    else {
      printf("your %s is %s\n", name, env_p); // prints PATH value
    }
  }

  void handle_pwd (void) {
    char dir[100];
    if(getcwd(dir, 100) == NULL){ //gets working directory
      fprintf(stderr, "Failed to get current directory");
    }
    else{
      printf("Your current working directory is:\n%s\n", dir); //prints working directory
    }
  }

  void handle_cd (char *input) {
    char prevDir[100];
    char currentDir[100];
    char *newDir = input + 3; //skips past "cd " part of input

    if(getcwd(prevDir, 100) == NULL){
      fprintf(stderr, "Failed to get current directory");
    }
    if(chdir(newDir) != 0){ //change the current directory
      fprintf(stderr, "Directory failed to change");
    }
    else{
      printf("Directory changed from:\n%s\nto:\n%s\n", prevDir, getcwd(currentDir,100));
    }
  }
  
