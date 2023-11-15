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

#endif /* SHELL_H */
