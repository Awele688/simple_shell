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
	char *direct = shargs[1];
	char cwd[PATH_MAX];

	if (direct == NULL)
	{
		direct = getenv("$HOME");
		if (direct == NULL)
		{
			perror("Error in sh_cd: getting HOME directory\n");
			return (-1);
		}
	}
	else if (strcmp(direct, "-") == 0)
	{
		direct = getenv("OPWD");
		if (direct == NULL)
		{
			perror("Error in sh_cd: changing dir to OPWD\n");
			return (-1);
		}
		write(STDOUT_FILENO, direct, strlen(direct));
		write(STDOUT_FILENO, "\n", 1);
	}
	if (getcwd(cwd, sizeof(cwd)) == NULL)
	{
		perror("Error in sh_cd: gets cwd\n");
		return (-1);
	}
	if (chdir(direct) == -1)
	{
		perror("Error in sh_cd: changing directory\n");
		return (-1);
	}
	if (setenv("PWD", getcwd(cwd, sizeof(cwd)), 1) != 0 ||
		setenv("OPWD", cwd, 1) != 0)
	{
		perror("Error in sh_cd: sets env. variables\n");
		return (-1);
	}
	return (0);
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
/**
 * shell_setenv - Initialize a new environment variable
 * @shargs: Arguments
 * Return: 0
 */
int shell_setenv(char **shargs)
{
	if (shargs[1] == NULL || shargs[2] == NULL)
	{
		write(STDERR_FILENO, "Usage: setenv VARIABLE VAL\n",
		strlen("Usage: setenv VARIABLE VAL\n"));
		return (-1);
	}
	if (setenv(shargs[1], shargs[2], 1) != 0)
	{
		perror("Error in shell_setenv: sets env. variables\n");
		return (-1);
	}
	return (0);
}
/**
 * shell_unsetenv - Remove an environment variable
 * @shargs: Arguments
 * Return: 0
 */
int shell_unsetenv(char **shargs)
{
	if (shargs[1] == NULL)
	{
		write(STDERR_FILENO, "Usage: unsetenv VARIABLE VAL\n",
		strlen("Usage: unsetenv VARIABLE VAL\n"));
		return (-1);
	}
	if (unsetenv(shargs[1]) != 0)
	{
		perror("Error in shell_unsetenv: unsets env. variables\n");
		return (-1);
	}
	return (0);
}
