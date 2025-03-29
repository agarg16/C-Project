#include <stdio.h>
#include <string.h>
#include <stdlib.h>

int main () {
    char *userInput = malloc(50);
    do {
        printf("Input: ");
        scanf("%50s", userInput);
        getchar();
    }
    while (strcmp(userInput, "exit") != 0 && strcmp(userInput, "Exit") != 0);

    printf("Exiting...");

    return 0;
}