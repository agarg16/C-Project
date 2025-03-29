#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include "builtInCmds.h"
#include "getFirstArg.h"

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
    char *firstArg;

    if(strlen(input) > 0){
      //isolate first command
      firstArg = getFirstArg(input);
      //loop through the built in commands, if match found execute builtin
      loopBuiltInCmds(firstArg, input);
	
      free(firstArg);
      firstArg = NULL;
      continue;
    }
    else if(strlen(input) == 0){ //user simply hits enter
      continue;
    }

    printf("%s: command not found\n", input);

  
  }

  return 0;
  
}
