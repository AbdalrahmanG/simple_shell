#include "shell.h"

/**
 * _ErroAotoi - for converting specific string to int
 *
 * @s: the converted string
 *
 * Return: not found 0, otherwise -1
 */

int _ErroAotoi(char *s)
{
	int io = 0;
	unsigned long int outCome = 0;

	if (*s == '+')
		s++;
	for (io = 0;  s[io] != '\0'; io++)
	{
		if (s[io] >= '0' && s[io] <= '9')
		{
			outCome *= 10;
			outCome += (s[io] - '0');
			if (outCome > INT_MAX)
				return (-1);
		}
		else
			return (-1);
	}
	return (outCome);
}

/**
 * print_error - for printing msg error
 *
 * @INfor: the used parameter
 * @estr: string has error type
 *
 * Return: not found 0, otherwise -1
 */

void print_error(info_t *INfor, char *estr)
{
	_ErrPutos(INfor->fname);
	_ErrPutos(": ");
	print_dicm(INfor->line_count, STDERR_FILENO);
	_ErrPutos(": ");
	_ErrPutos(INfor->argv[0]);
	_ErrPutos(": ");
	_ErrPutos(estr);
}

/**
 * print_dicm - for printing deci number that has 10 base
 *
 * @input: the input used here
 * @file_Def: the written filedescriptor
 *
 * Return: the printed number
 */

int print_dicm(int input, int file_Def)
{
	int (*_PutPcharc)(char) = _PutPcharc;
	int io, cunt = 0;
	unsigned int _abslo_, NowCurr;

	if (file_Def == STDERR_FILENO)
		_PutPcharc = _ErrPutochar;
	if (input < 0)
	{
		_abslo_ = -input;
		_PutPcharc('-');
		cunt++;
	}
	else
		_abslo_ = input;
	NowCurr = _abslo_;
	for (io = 1000000000; io > 1; io /= 10)
	{
		if (_abslo_ / io)
		{
			_PutPcharc('0' + NowCurr / io);
			cunt++;
		}
		NowCurr %= io;
	}
	_PutPcharc('0' + NowCurr);
	cunt++;

	return (cunt);
}

/**
 * Con_verNum - for convertering func.of iatoa
 *
 * @num: used number
 * @base: used base
 * @flags: specific argument flags
 *
 * Return: used string
 */

char *Con_verNum(long int num, int base, int flags)
{
	static char *arro;
	static char buffer[50];
	char sn = 0;
	char *ptro;
	unsigned long n = num;

	if (!(flags & CONVERT_UNSIGNED) && num < 0)
	{
		n = -num;
		sn = '-';

	}
	arro = flags & CONVERT_LOWERCASE ? "0123456789abcdef" : "0123456789ABCDEF";
	ptro = &buffer[49];
	*ptro = '\0';

	do	{
		*--ptro = arro[n % base];
		n /= base;
	} while (n != 0);

	if (sn)
		*--ptro = sn;
	return (ptro);
}

/**
 * remove_comments - for replacing first copy of '#' with big 0
 *
 * @buf: the modified string addrs
 *
 * Return: success only 0;
 */

void remove_comments(char *buf)
{
	int io;

	for (io = 0; buf[io] != '\0'; io++)
		if (buf[io] == '#' && (!io || buf[io - 1] == ' '))
		{
			buf[io] = '\0';
			break;
		}
}

