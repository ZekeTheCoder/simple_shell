#include "shell.h"

/**
 * displayPrompt - Display the shell prompt
 *
 * Return: no return
 */
void displayPrompt(void)
{
	if (isatty(STDIN_FILENO))
		write(STDOUT_FILENO, "$ ", 3);
}

/**
 * executeCommand - executes commands
 * @inputBuffer: user input
 *
 * Return: no return
 */
void executeCommand(char *inputBuffer)
{
	pid_t childPid;
	int childStatus;

	/* Create a child process */
	childPid = fork();

	if (childPid == -1)
	{
		perror("child creation failed.");
		exit(EXIT_FAILURE);
	}

	if (childPid == 0)
	{
		char *command[2];

		command[0] = inputBuffer;
		command[1] = NULL;

		if (execve(inputBuffer, command, environ) == -1)
		{
			perror("./shell");
			exit(1);
		}
	}
	else
	{
		wait(&childStatus);
	}
}

/**
 * main - Entry point of our program
 *
 * Return: no return
 */
int main(void)
{
	char *inputBuffer = NULL;
	size_t bufferSize = 0;
	ssize_t bytesRead;

	while (1)
	{
		displayPrompt();
		bytesRead = getline(&inputBuffer, &bufferSize, stdin);

		if (bytesRead == -1)
		{
			free(inputBuffer);
			exit(1);
		}

		if (inputBuffer[bytesRead - 1] == '\n')
			inputBuffer[bytesRead - 1] = '\0';

		executeCommand(inputBuffer);
	}
	free(inputBuffer);
	return (0);
}
