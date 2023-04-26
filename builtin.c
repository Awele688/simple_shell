#include "shell.h"
/**
 * sh_exit - A function that exit the shell as and when needed
 * @shargs: A character string
 * Return: 0 if success or with status
 */
int sh_exit(char **shargs)
{
	int status = 0;
	if (shargs[1] != NULL)
	{
		status = (atoi(shargs[1]));
	}
	_exit(status);
}
/**
 * sh_cd - A function that changes the directory of the shell
 * @shargs: A double pointer to character string
 * Return: -1 if success
 */
int sh_cd(char **shargs)
{
	if (shargs[1] == NULL)
	{
		write(STDERR_FILENO, "Expected argument to \"cd \"\n",
				strlen("Expected argument to \"cd \"\n"));
	}
	else
	{
		if (chdir(shargs[1]) != 0)
		{
			perror("Error in sh_cd: changing dir\n");
		}
	}
	return (-1);
}
/**
 * sh_env - A function that outputs environment variables
 * @shargs: Arguments
 * Return: -1 if success
 */
int sh_env(__attribute__((unused))char **shargs)
{
	int x = 0;

	while (environ[x])
	{
		write(STDOUT_FILENO, environ[x], strlen(environ[x]));
		write(STDOUT_FILENO, "\n", 1);
		x++;
	}
	return (-1);
}
