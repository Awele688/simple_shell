#ifndef SHELL_H
#define SHELL_H

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <sys/types.h>
#include <sys/wait.h>

#define SHELL_BUFFERSIZE 1024
#define BUFFERSIZE 64
#define DELIMITERS " \n\t\r\""
#define TRUE 1

extern char **environ;

int _putchar(char c);
char *callshelline(void);
void interactive_shell(void);
void uninteractive_shell(void);
char *readshelline(void);
char **splitshell(char *shline);
int shell_builtin(void);
int execute(char **shargs);
int newshell_process(char **shargs);
int sh_exit(char **shargs);
int sh_env(__attribute__((unused))char **shargs);
int sh_cd(char **shargs);
int mystrcmp(const char *str1, const char *str2);
size_t mystrlen(const char *b);
void *mymemcpy(void *dest, const void *src, size_t x);
char *mystrdup(const char *i);
#endif
