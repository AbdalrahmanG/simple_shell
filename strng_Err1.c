#include "shell.h"

/**
 ** _Strgcop - for coping the used string
 *
 * @dest: the useed destination string
 * @src: the given string source
 * @n: the space of characters copied
 *
 * -Return: string
 */

char *_Strgcop(char *dest, char *src, int n)
{
	int io, jo;
	char *s = dest;

	io = 0;
	while (src[io] != '\0' && io < n - 1)
	{
		dest[io] = src[io];
		io++;
	}
	if (io < n)
	{
		jo = io;
		while (jo < n)
		{
			dest[jo] = '\0';
			jo++;
		}
	}
	return (s);
}

/**
 ** _strngconc - for concatenating 2 strings
 *
 * @dest: first string to be used
 * @src: second string to be used
 * @n: the space bytes max used
 *
 * Return: string
 */

char *_strngconc(char *dest, char *src, int n)
{
	int io, jo;
	char *s = dest;

	io = 0;
	jo = 0;
	while (dest[io] != '\0')
		io++;
	while (src[jo] != '\0' && jo < n)
	{
		dest[io] = src[jo];
		io++;
		jo++;
	}
	if (jo < n)
		dest[io] = '\0';
	return (s);
}

/**
 * _strngCharc - for locating a character string
 *
 * @s: the parded string in shell
 * @c: the looked for characterin shell
 *
 * Return: pointer of memory
 */

char *_strngCharc(char *s, char c)
{
	do {
		if (*s == c)
			return (s);
	} while (*s++ != '\0');

	return (NULL);
}

/**
 * **strng_in2 - for spliting string into some words
 *
 * @str: the inputed string here
 * @d: the delimetered string here
 *
 * Return: string pointer
 */

char **strng_in2(char *str, char *d)
{
	int io, jo, Ko, mo;
	int numToWords = 0;
	char **so;

	if (str == NULL || str[0] == 0)
		return (NULL);
	if (!d)
		d = " ";
	for (io = 0; str[io] != '\0'; io++)
		if (!Chk_delim(str[io], d) && (Chk_delim(str[io + 1], d) || !str[io + 1]))
			numToWords++;

	if (numToWords == 0)
		return (NULL);
	so = malloc((1 + numToWords) * sizeof(char *));
	if (!so)
		return (NULL);
	for (io = 0, jo = 0; jo < numToWords; jo++)
	{
		while (Chk_delim(str[io], d))
			io++;
		Ko = 0;
		while (!Chk_delim(str[io + Ko], d) && str[io + Ko])
			Ko++;
		so[jo] = malloc((Ko + 1) * sizeof(char));
		if (!so[jo])
		{
			for (Ko = 0; Ko < jo; Ko++)
				free(so[Ko]);
			free(so);
			return (NULL);
		}
		for (mo = 0; mo < Ko; mo++)
			so[jo][mo] = str[io++];
		so[jo][mo] = 0;
	}
	so[jo] = NULL;
	return (so);
}

/**
 * **strng_in22 - for spliting a string into words for shell
 *
 * @str: the inputed string here
 * @d: the delimeter used here
 *
 * Return: strin pointer or null
 */

char **strng_in22(char *str, char d)
{
	int io, jo, Ko, mo, numToWords = 0;
	char **so;

	if (str == NULL || str[0] == 0)
		return (NULL);
	for (io = 0; str[io] != '\0'; io++)
		if ((str[io] != d && str[io + 1] == d) ||
		    (str[io] != d && !str[io + 1]) || str[io + 1] == d)
			numToWords++;
	if (numToWords == 0)
		return (NULL);
	so = malloc((1 + numToWords) * sizeof(char *));
	if (!so)
		return (NULL);
	for (io = 0, jo = 0; jo < numToWords; jo++)
	{
		while (str[io] == d && str[io] != d)
			io++;
		Ko = 0;
		while (str[io + Ko] != d && str[io + Ko] && str[io + Ko] != d)
			Ko++;
		so[jo] = malloc((Ko + 1) * sizeof(char));
		if (!so[jo])
		{
			for (Ko = 0; Ko < jo; Ko++)
				free(so[Ko]);
			free(so);
			return (NULL);
		}
		for (mo = 0; mo < Ko; mo++)
			so[jo][mo] = str[io++];
		so[jo][mo] = 0;
	}
	so[jo] = NULL;
	return (so);
}

