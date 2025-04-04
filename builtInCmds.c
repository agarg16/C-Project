#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include "builtInCmds.h"
#include "argControl.h"

  //array of built in commands
  char *builtInList[] = { //order must match builtInFunctions order
    "echo",
    "exit",
    "type",
    "pwd",
    "cd"
  };

  short numBuiltIns = sizeof(builtInList) / sizeof(char*);

  //array of built in command functions
  void (*builtInFunctions[])(char *, char **) = { //order must match builtInList order
    &handle_echo,
    &handle_exit,
    &handle_type,
    &handle_pwd,
    &handle_cd
  };

  void handle_echo (char *input, char **args) {
    char *message = input + strlen("echo"); // gets everything after "echo"
    
    while (*message == ' ') { // checks if there's a space after echo
      message++; // skips space in char array after "echo"
    }
    printf("%s\n", message); // prints rest of the input after skipping space
  
  }
  
  void handle_exit (char *input, char **args) {
    freeArgs(args);
    exit(0); // exits program
  }
  
  void handle_type (char *arg, char **args) {
    arg = arg + 5;
    if (strcmp(arg, "echo") == 0) { // check if argument is "echo"
      printf("echo is a shell builtin\n");
    } else if (strcmp(arg, "exit") == 0) { // check if argument is "exit"
      printf("exit is a shell builtin\n");
    } else if (strcmp(arg, "type") == 0) { // check if argument is "type"
      printf("type is a shell builtin\n"); 
    } else if (strcmp(arg, "cd") == 0) { // check if argument is "cd"
      printf("cd is a shell builtin\n");
    }else if (strcmp(arg, "pwd") == 0) { // check if argument is "pwd"
      printf("pwd is a shell builtin\n");
    }else {
      printf("%s: not found\n", arg);
    }
  }
  
  void handle_path (char *arg, char **args) {
    const char *name = "PATH"; // name of environment variable
    const char *env_p = getenv(name); // gets value of environment variable
    if (env_p == NULL) {
      printf("%s: not set\n", name); 
    }
    else {
      printf("your %s is %s\n", name, env_p); // prints PATH value
    }
  }

  void handle_pwd (char *input, char **args) {
    char dir[100];
    if(getcwd(dir, 100) == NULL){ //gets working directory
      fprintf(stderr, "Failed to get current directory");
    }
    else{
      printf("Your current working directory is:\n%s\n", dir); //prints working directory
    }
  }

  void handle_cd (char *input, char **args) {
    char prevDir[100];
    char currentDir[100];
    char *newDir = input + 3; //skips past "cd " part of input

    if(getcwd(prevDir, 100) == NULL){
      fprintf(stderr, "Failed to get current directory\n");
    }
    if(chdir(newDir) != 0){ //change the current directory
      fprintf(stderr, "Directory failed to change\n");
    }
    else{
      printf("Directory changed from:\n%s\nto:\n%s\n", prevDir, getcwd(currentDir,100));
    }

    
  }

  int loopBuiltInCmds(char *arg, char *input, char **args) { 
    for(int i = 0; i < numBuiltIns; i++){ //loop through commands
      if(strcmp(arg, builtInList[i]) == 0){ //check if first arg is a built in
        (*builtInFunctions[i])(input, args);//execute the builtin and pass it the full input
        return 1; //executed a builtin
      }
    }
    return 0; //did not execute a builtin
  }
  
