#include "shell.h"

/**
 * _strDouble - for duplicating a specific string
 * @str: the used duplicated string
 *
 * Return: duplicated string pointer
 */

char *_strDouble(const char *str)
{
	int leo = 0;
	char *reto;

	if (str == NULL)
		return (NULL);
	while (*str++)
		leo++;
	reto = malloc(sizeof(char) * (leo + 1));
	if (!reto)
		return (NULL);
	for (leo++; leo--;)
		reto[leo] = *--str;
	return (reto);
}

/**
 *_PutPs - for printing the used input string

 *@str: the printed strng
 *
 * Return:  void (Nothing)
 */

void _PutPs(char *str)
{
	int io = 0;

	if (!str)
		return;
	while (str[io] != '\0')
	{
		_PutPcharc(str[io]);
		io++;
	}
}

/**
 * _PutPcharc - for writing char c to output
 *
 * @c: The printed char
 *
 * Return: success 1,fail -1
 */

int _PutPcharc(char c)
{
	static int io;
	static char buf[WRITE_BUFF_SSIZE];

	if (c == BUFF_FRFLUSH || io >= WRITE_BUFF_SSIZE)
	{
		write(1, buf, io);
		io = 0;
	}
	if (c != BUFF_FRFLUSH)
		buf[io++] = c;
	return (1);
}

