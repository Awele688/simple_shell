#include "shell.h"

void uninteractive_shell(void)
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
