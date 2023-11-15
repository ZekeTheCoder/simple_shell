#include "shell.h"

/**
 * displayPrompt - Display the shell prompt
 *
 * Return: no return
 */
void displayPrompt(void)
{
	write(STDOUT_FILENO, "$ ", 3);
}

/**
 * handleInputError - handles user input errors
 * @bytesRead: number of bytes read during an input operation.
 *
 * Return: no return
 */
void handleInputError(ssize_t bytesRead)
{
	if (bytesRead == -1)
	{
		/*perror("Shell Exit");*/
		exit(1);
	}
}

/**
 * createChildProcess - Creates a child process using the fork system call.
 *
 * Return: PID of the newly created child process for the parent,
 * or 0 for the child.
 */
pid_t createChildProcess(void)
{
	pid_t child_pid = fork();

	if (child_pid == -1)
	{
		perror("child creation failed.");
		exit(EXIT_FAILURE);
	}

	return (child_pid);
}

/**
 * runSimpleShell - runs our simple shell
 *
 * Return: no return
 */
void runSimpleShell(void)
{
	char *inputBuffer = NULL;
	size_t bufferSize = 0;
	ssize_t bytesRead;
	pid_t child_pid;
	int child_status;

	while (1)
	{
		if (isatty(STDIN_FILENO))
			displayPrompt();

		bytesRead = getline(&inputBuffer, &bufferSize, stdin);
		handleInputError(bytesRead);

		if (inputBuffer[bytesRead - 1] == '\n')
			inputBuffer[bytesRead - 1] = '\0';

		/* Create a child process */
		child_pid = createChildProcess();

		if (child_pid == 0)
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
			wait(&child_status);
		}
	}

	free(inputBuffer);
}
