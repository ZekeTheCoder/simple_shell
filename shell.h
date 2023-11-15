#ifndef SHELL_H
#define SHELL_H

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>

#include <sys/types.h>
#include <sys/wait.h>

extern char **environ;
void displayPrompt(void);
void runSimpleShell(void);
void handleInputError(ssize_t bytesRead);
pid_t createChildProcess(void);

#endif /* SHELL_H */
