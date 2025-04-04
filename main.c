#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include "builtInCmds.h"
#include "argControl.h"
#include "startProcess.h"

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
    char **args = separateArgs(input); //separate all arguments in a string array

    if(strlen(input) > 0){
      
      int execBuiltIn;
      //loop through the built in commands, if match found execute builtin
      execBuiltIn = loopBuiltInCmds(args[0], input, args); //returns 1 if a builtin was executed and 0 if not
      if(!execBuiltIn){ //if command wasn't a built try running the process
        startProcess(args);
      }

      freeArgs(args);
      continue;
    }
    else if(strlen(input) == 0){ //user simply hits enter
      freeArgs(args);
      continue;
      }

      freeArgs(args);

  }
  

  return 0;
  
}
