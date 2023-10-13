#include "shell.h"

/**
 * _ErrPutos - for printing the input
 *
 * @str: string
 *
 * Return: void (no thing)
 */

void _ErrPutos(char *str)
{
	int io = 0;

	if (!str)
		return;
	while (str[io] != '\0')
	{
		_ErrPutochar(str[io]);
		io++;
	}
}

/**
 * _ErrPutochar - for writing char c at str
 *
 * @c: The printed char
 *
 * Return: success 1.otherwise -1
 */

int _ErrPutochar(char c)
{
	static int io;
	static char buf[WRITE_BUFF_SSIZE];

	if (c == BUFF_FRFLUSH || io >= WRITE_BUFF_SSIZE)
	{
		write(2, buf, io);
		io = 0;
	}
	if (c != BUFF_FRFLUSH)
		buf[io++] = c;
	return (1);
}

/**
 * _putfile_Def - for writing char c at curr file_Def
 *
 * @c: The prnted char
 * @file_Def: write at filedescriptor
 *
 * Return: success 1.otherwise -1
 */

int _putfile_Def(char c, int file_Def)
{
	static int io;
	static char buf[WRITE_BUFF_SSIZE];

	if (c == BUFF_FRFLUSH || io >= WRITE_BUFF_SSIZE)
	{
		write(file_Def, buf, io);
		io = 0;
	}
	if (c != BUFF_FRFLUSH)
		buf[io++] = c;
	return (1);
}

/**
 *_PutPsfile_Def - for printing input stro

 * @str: string only that
 * @file_Def: write at filedescriptor
 *
 * Return: charachter in put numb
 */

int _PutPsfile_Def(char *str, int file_Def)
{
	int io = 0;

	if (!str)
		return (0);
	while (*str)
	{
		io += _putfile_Def(*str++, file_Def);
	}
	return (io);
}

