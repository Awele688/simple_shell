#include "shell.h"

/**
 * interactive_shell - A shell that engages a user
 * Return: void
 */

void interactive_shell(void)
{
	char *shline, **shargs;
	int state;

	do {
		write(STDOUT_FILENO, "myshell($) ", 11);
		shline = readshline();
		shargs = splitit(shline);
		state = execute(shargs);
	free(shline);
	free(shargs);
	} while (state);
}
/**
 * readshline - A function that reads the line from the shell input
 * Return: void
 */
char *readshline(void)
{
	int buffsize = SHELL_BUFFERSIZE, pos = 0, v;
	char *buffer;

	buffer = malloc(sizeof(char) * buffsize);
	if (buffer == NULL)
	{
		perror("myshell: Allocation problems\n");
		exit(EXIT_FAILURE);
	}
	while ((v = getchar()) != EOF && v == '\n')
	{
		buffer[pos] = v;
		pos++;
	if (pos >= buffsize)
	{
		buffsize += SHELL_BUFFERSIZE;
		buffer = realloc(buffer, buffsize);
		if (buffer == NULL)
		{
			perror("myshell: Allocation problems\n");
			exit(EXIT_FAILURE);
		}
	}
	}
	buffer[pos] = '\0';
	return (buffer);
}
/**
 * splitit - The function takes the string passed and splits into tokens
 * @shline: A pointer to character string passed to the shell
 * Return: character if successful
 */
char **splitit(char *shline)
{
	int x = 0, buff = BUFFERSIZE;
	char **toks, *token, *ptr;

	toks = malloc(buff * sizeof(char *));
	if (toks == NULL)
	{
		perror("Allocation problems when splitting the line\n");
		exit(EXIT_FAILURE);
	}
	token = strtok_r(shline, DELIMITERS, &ptr);
	while (token != NULL)
	{
		if (token[0] == '#')
		{
			break;
		}
	toks[x] = token;
	x++;
	if (x >= buff)
	{
		buff += buff;
		toks = realloc(toks, buff * sizeof(char *));
		if (toks == NULL)
		{
			perror("Allocation problems when splitting the line\n");
			exit(EXIT_FAILURE);
		}
	}
		token = strtok_r(NULL, DELIMITERS, &ptr);
	}
	toks[x] = NULL;
	return (toks);
}
/**
 * execute - A function that executes a builtin command or start a new process
 * @shargs: A double pointer to command and its flags
 * Return: 0 if success or otherwise
 */
int execute(char **shargs)
{
	long unsigned int i;

	char *builtin_list[] = {"cd", "env", "exit"};

	int (*builtin_func[])(char **) = {&sh_cd, &sh_env, &sh_exit};

	if (shargs == NULL)
	{
		return (-1);
	}
	for (i = 0; i < sizeof(builtin_list) / sizeof(char *); i++)
	{
		if (strcmp(shargs[0], builtin_list[i]) == 0)
		{
			return ((*builtin_func[i])(shargs));
		}
	}
	return (newshell_process(shargs));
}
