#include "shell.h"

/**
 * FreeingPoin - for freeing pointer & address
 *
 * @ptro: address of the pointer to free
 *
 * Return: success 1, otherwise 0.
 */

int FreeingPoin(void **ptro)
{
	if (ptro && *ptro)
	{
		free(*ptro);
		*ptro = NULL;
		return (1);
	}
	return (0);
}

