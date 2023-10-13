#include "shell.h"

/**
 * *_memset - for filling memory with constant byte
 *
 * @s: specific memory area pointer
 * @b: filled *s with bytes
 * @n: the specific filled bytes
 *
 * - Return: memory area pointer as usual
 */

char *_memset(char *s, char b, unsigned int n)
{
	unsigned int io;

	for (io = 0; io < n; io++)
		s[io] = b;
	return (s);
}

/**
 * DobyFree - for freeing string of strings
 *
 * @pp: the specific string of strings
 */

void DobyFree(char **pp)
{
	char **a = pp;

	if (!pp)
		return;
	while (*pp)
		free(*pp++);
	free(a);
}

/**
 * _realloc - for reallocating the memory block
 *
 * @ptro: pointer to malloc
 * @old_size: byte space of previous-block
 * @new_size: byte space of new-block
 *
 * Return: the used pointer
 */

void *_realloc(void *ptro, unsigned int old_size, unsigned int new_size)
{
	char *p;

	if (!ptro)
		return (malloc(new_size));
	if (!new_size)
		return (free(ptro), NULL);
	if (new_size == old_size)
		return (ptro);

	p = malloc(new_size);
	if (!p)
		return (NULL);

	old_size = old_size < new_size ? old_size : new_size;
	while (old_size--)
		p[old_size] = ((char *)ptro)[old_size];
	free(ptro);
	return (p);
}

