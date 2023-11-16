#include "shell.h"

/**
 * tokenizeInput - Tokenizes the user input buffer
 * and stores the resulting tokens in an array.
 *
 * @inputBuffer: The user input buffer to be tokenized
 * @tokenArray:  The array to store the resulting tokens.
 *
 * Return: no return
 */
void tokenizeInput(char *inputBuffer, char **tokenArray)
{
	char *token;
	int i;

	token = strtok(inputBuffer, " ");
	for (i = 0; token; i++)
	{
		tokenArray[i] = token;
		token = strtok(NULL, " \n");
	}

	tokenArray[i] = NULL;
}

/**
 * executeAbsoluteCommand - Executes a command given its absolute path.
 *
 * @tokenArray: The array containing the command and its arguments.
 * @env: The environment variables.
 *
 * Return: no return
 */
void executeAbsoluteCommand(char **tokenArray, char **env)
{
	if (access(tokenArray[0], X_OK) == 0)
	{
		if (execve(tokenArray[0], tokenArray, env) == -1)
		{
			perror("./shell");
			exit(EXIT_FAILURE);
		}
	}
	else
	{
		fprintf(stderr, "./shell: %s: No such file or directory\n", tokenArray[0]);
		exit(EXIT_FAILURE);
	}
}

/**
 * searchInPath - Searches for and executes a command in directories
 * specified in the PATH environment variable.
 *
 * @tokenArray: The array containing the command and its arguments.
 * @env: The environment variables.
 *
 * Return: no return
 */
void searchInPath(char **tokenArray, char **env)
{
	char *path = getenv("PATH");

	char *pathToken;
	char **pathDirs = malloc(sizeof(char *) * 1024);
	int j = 0, k;

	pathToken = strtok(path, ":");
	while (pathToken != NULL)
	{
		pathDirs[j++] = pathToken;
		pathToken = strtok(NULL, ":");
	}

	for (k = 0; k < j; k++)
	{
		char *execPath = malloc(strlen(pathDirs[k]) + strlen(tokenArray[0]) + 2);

		sprintf(execPath, "%s/%s", pathDirs[k], tokenArray[0]);

		if (execve(execPath, tokenArray, env) != -1)
		{
			free(pathDirs);
			free(execPath);
			exit(EXIT_SUCCESS);
		}
		free(execPath);
	}

	perror("./shell");
	free(pathDirs);
	exit(EXIT_FAILURE);
}
