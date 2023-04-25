#include "shell.h"

/**
 * newshell_process - A function that creates a new process
 * @shargs: A double pointer to array of strings that contain builtin commands
 * Return: -1 if failure 0 if success
 */
int newshell_process(char **shargs)
{
	pid_t pid;
	int status;

	pid = fork();
	if (pid == 0)
	{
		if (execve(shargs[0], shargs, environ) == -1)
		{
			perror("error in the new process");
			exit(EXIT_FAILURE);
		}
	}
	else if (pid < 0)
	{
		perror("error in the forking process");
	}
	else
	{
		do {
			waitpid(pid, &status, WUNTRACED);
		} while (!WIFEXITED(status) && !WIFSIGNALED(status));
	}
	return (-1);
}
