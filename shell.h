#ifndef SHELL_H
#define SHELL_H

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>

#include <sys/types.h>
#include <sys/wait.h>

void displayPrompt(void);
void executeCommand(char *inputBuffer, char **env);
/*helper functions*/
void tokenizeInput(char *inputBuffer, char **tokenArray);
void executeAbsoluteCommand(char **tokenArray, char **env);
void searchInPath(char **tokenArray, char **env);

#endif /* SHELL_H */
