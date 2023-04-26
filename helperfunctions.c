#include "shell.h"
/**
 * mystrdup - A function that allocates new memory
 * @i: A pointer to char
 * Return: the newstring
 */
char *mystrdup(const char *i)
{
	size_t length = mystrlen(i);
	char *newstring;

	newstring = malloc(length + 1);
	if (newstring == NULL)
	{
		return (NULL);
	}
	mymemcpy(newstring, i, length + 1);
	return (newstring);
}
/**
 * mymemcpy - A function that copies from one string to another
 * @dest: the string to return
 * @src: the string to be copied
 * @x: the number of bytes to be copied
 * Return: the final string that is dest
 */
void *mymemcpy(void *dest, const void *src, size_t x)
{
	char *s = dest;
	const char *r = src;

	while (x--)
	{
		*s++ = *r++;
	}
	return (dest);
}
/**
 * mystrlen - Funtion that returns the length of a string
 * @b: A pointer to a constant character
 * Return: length of string
 */
size_t mystrlen(const char *b)
{
	const char *s = b;

	while (*s)
	{
		s++;
	}
	return (s - b);
}
/**
 * mystrcmp - A function that compares two strings
 * @str1: A pointer to first string
 * @str2: A pointer to second string
 * Return: the compared string if possible
 */
int mystrcmp(const char *str1, const char *str2)
{
	int c = 0;

	while (str1[c] == str2[c])
	{
		if (str1[c] == '\0')
		{
			return (0);
		}
	c++;
	}
	if (str1[c] < str2[c])
	{
		return (-1);
	}
	else
	{
		return (1);
	}
}
