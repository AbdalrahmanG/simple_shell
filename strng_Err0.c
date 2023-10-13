#include "shell.h"

/**
 * _StrngLnth - for returning string length
 *
 * @s: the checked string lenth
 *
 * Return: string lenth
 */

int _StrngLnth(char *s)
{
	int io = 0;

	if (!s)
		return (0);

	while (*s++)
		io++;
	return (io);
}

/**
 * _StrngCmpr - for performing comparison of 2 strangs
 *
 * @s1:  first string here
 * @s2:  second strang here
 *
 * Return: negative, positive, 0
 */

int _StrngCmpr(char *s1, char *s2)
{
	while (*s1 && *s2)
	{
		if (*s1 != *s2)
			return (*s1 - *s2);
		s1++;
		s2++;
	}
	if (*s1 == *s2)
		return (0);
	else
		return (*s1 < *s2 ? -1 : 1);
}

/**
 * Begin_By - for checking is needle starts with haystack or not
 *
 * @haystack: the searched string
 * @needle: to find substring in shell
 *
 * Return: address of chara
 */

char *Begin_By(const char *haystack, const char *needle)
{
	while (*needle)
		if (*needle++ != *haystack++)
			return (NULL);
	return ((char *)haystack);
}

/**
 * _StrngCat - for concatenating the 2 strings
 *
 * @dest: the used destination buff
 * @src: the source used in buff
 *
 * Return: buff pointer
 */

char *_StrngCat(char *dest, char *src)
{
	char *reto = dest;

	while (*dest)
		dest++;
	while (*src)
		*dest++ = *src++;
	*dest = *src;
	return (reto);
}

/**
 * _StrnCpy - for coping the given string
 *
 * @dest: the used destinat
 * @src: the used source
 *
 * Return: used destination pointer
 */

char *_StrnCpy(char *dest, char *src)
{
	int io = 0;

	if (dest == src || src == 0)
		return (dest);
	while (src[io])
	{
		dest[io] = src[io];
		io++;
	}
	dest[io] = 0;
	return (dest);
}
