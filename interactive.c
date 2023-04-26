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
		shline = readshelline();
		shargs = splitshell(shline);
		state = execute(shargs);
	free(shline);
	free(shargs);
	} while (state);
}
/**
 * readshelline - A function that reads the line from the shell input
 * Return: void
 */
char *readshelline(void)
{
	int buffsize = SHELL_BUFFERSIZE, pos = 0, v;
	char *buffer;

	buffer = malloc(sizeof(char) * buffsize);
	if (buffer == NULL)
	{
		perror("myshell: Allocation problems\n");
		exit(EXIT_FAILURE);
	}
	while (TRUE)
	{
		v = getchar();
		if (v == EOF)
		{
			free(buffer);
			_putchar('\n');
			exit(EXIT_SUCCESS);
		}
		if (v == '\n')
		{
			buffer[pos] = '\0';
			return (buffer);
		}
		else
		{
			buffer[pos] = v;
		}
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
	return (0);
}
/**
 * splitshell - The function takes the string passed and splits into tokens
 * @shline: A pointer to character string passed to the shell
 * Return: character if successful
 */
char **splitshell(char *shline)
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
	unsigned long int i;

	char *builtin_list[] = {"cd", "env", "exit", "setenv", "unsetenv"};

	int (*builtin_func[])(char **) = {&sh_cd, &sh_env, &sh_exit,
		&shell_setenv, &shell_unsetenv};

	if (shargs == NULL)
	{
		return (-1);
	}
	for (i = 0; i < sizeof(builtin_list) / sizeof(*builtin_list); i++)
	{
		if (strcmp(shargs[0], builtin_list[i]) == 0)
		{
			return ((*builtin_func[i])(shargs));
		}
	}
	return (newshell_process(shargs));
}

/**
 * _putchar - writes the character c to stdout
 * @c: The character to print
 *
 * Return: On success 1.
 * On error, -1 is returned, and errno is ser appropriately.
 */
int _putchar(char c)
{
	return (write(1, &c, 1));
}
