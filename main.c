#include "shell.h"
/**
 * main - Entry point to shell function
 * @argc: Argument count from the terminal
 * @argv: Argument vector from the terminal
 * Return: 0 if successful
 */
int main(void)
{
	if (isatty(STDIN_FILENO) == 1)
	{
		interactive_shell();
	}
	else
	{
		uninteractive_shell();
	}
	return (0);
}
