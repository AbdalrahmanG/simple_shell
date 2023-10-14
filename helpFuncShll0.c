#include "shell.h"

/**
 * SllInteractivate - for returning 1 when shell in interactive mode
 *
 * @INfor: struct's address that is used
 *
 * Return: interactive mode 1(success) ,otherwise 0
 */

int SllInteractivate(info_t *INfor)
{
	return (isatty(STDIN_FILENO) && INfor->readfile_Def <= 2);
}

/**
 * Chk_delim - for checking character is delimeter or not
 *
 * @c: the checked char
 * @delim: used delimeter string
 *
 * Return: success 1,fail 0
 */

int Chk_delim(char c, char *delim)
{
	while (*delim)
		if (*delim++ == c)
			return (1);
	return (0);
}

/**
 *_ChkAlphap - for checking the alphabetic chara okay

 *@c: The inputed chara

 *Return: success 1 ,otherwise 0
 */

int _ChkAlphap(int c)
{
	if ((c >= 'a' && c <= 'z') || (c >= 'A' && c <= 'Z'))
		return (1);
	else
		return (0);
}

/**
 *_AtoiO - for converting specific string to int

 *@s: the converted string

 *Return: not found 0, otherwise the numb
 */

int _AtoiO(char *s)
{
	int io, sn = 1, flgo = 0, output;
	unsigned int OutCome = 0;

	for (io = 0;  s[io] != '\0' && flgo != 2; io++)
	{
		if (s[io] == '-')
			sn *= -1;

		if (s[io] >= '0' && s[io] <= '9')
		{
			flgo = 1;
			OutCome *= 10;
			OutCome += (s[io] - '0');
		}
		else if (flgo == 1)
			flgo = 2;
	}

	if (sn == -1)
		output = -OutCome;
	else
		output = OutCome;

	return (output);
}

