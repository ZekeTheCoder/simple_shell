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
 * @env: environ
 * Return: no return
 */
void executeCommand(char *inputBuffer, char **env)
{
	pid_t childPid;
	int childStatus;
	char *token;
	char **tokenArray;
	int i = 0;

	/* Create a child process */
	childPid = fork();

	if (childPid == -1)
	{
		perror("child creation failed.");
		exit(EXIT_FAILURE);
	}

	token = strtok(inputBuffer, " ");
	tokenArray = malloc(sizeof(char *) * 1024);

	for (i = 0; token; i++)
	{
		tokenArray[i] = token;
		token = strtok(NULL, " \n");
	}

	tokenArray[i] = NULL;

	if (childPid == 0)
	{
		if (execve(tokenArray[0], tokenArray, env) == -1)
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
 * main - Main entry point of our program
 * @argc: Argument count
 * @argv: Array of argument values pointer
 * @env: NULL terminated array of strings
 * Return: O Always success
 */
int main(int argc, char **argv, char **env)
{
	char *inputBuffer = NULL;
	size_t bufferSize = 0;
	ssize_t bytesRead;

	(void)argc;
	(void)argv;

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

		executeCommand(inputBuffer, env);
	}
	free(inputBuffer);
	return (0);
}
