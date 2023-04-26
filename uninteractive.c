#include "shell.h"
/**
 * uninteractive_shell - deals with the shell in an uninteractive state
 * Return: void
 */
void uninteractive_shell(void)
{
	char **shargs, *input;
	int state;

	do {
	input = callshelline();
	shargs = splitshell(input);
	state = execute(shargs);
	free(shargs);
	free(input);
	} while (state);
}

/**
 * callshelline - A function that reads the line from the shell input
 * Return: void
 */
char *callshelline(void)
{
	int buffsize = SHELL_BUFFERSIZE, pos = 0, v;
	char *buffer, *newbuffer;

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
			exit(EXIT_SUCCESS);
		}
		if (v == '\n')
		{
			buffer[pos] = '\0';
			return (buffer);
		}
		buffer[pos] = v;
		pos++;
		if (pos >= buffsize)
		{
			buffsize += SHELL_BUFFERSIZE;
			newbuffer = malloc(sizeof(char) * buffsize);
			if (newbuffer == NULL)
			{
				perror("myshell: Allocation problems\n");
				exit(EXIT_FAILURE);
			}
			mymemcpy(newbuffer, buffer, pos);
			free(buffer);
			buffer = newbuffer;
		}
	}
	return (0);
}
