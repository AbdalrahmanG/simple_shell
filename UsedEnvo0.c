#include "shell.h"

/**
 * _EnvoCuro - for printing current envo
 *
 * @INfor: Structure arguments
 *
 * -Return: success only 0
 */

int _EnvoCuro(info_t *INfor)
{
	List_ToBe_print_str(INfor->env);
	return (0);
}

/**
 * _getenv - for getting value of variable in environment
 *
 * @INfor: Structure arguments
 * @name: envo vasr name ithink
 *
 * -Return: outcome
 */

char *_getenv(info_t *INfor, const char *name)
{
	list_t *node = INfor->env;
	char *p;

	while (node)
	{
		p = Begin_By(node->str, name);
		if (p && *p)
			return (p);
		node = node->next;
	}
	return (NULL);
}

/**
 * _EnvoCuroiroSetter - for Initializing a lang environment variable
 *
 * @INfor: Structure arguments
 *
 * -Return: success only 0
 */

int _EnvoCuroiroSetter(info_t *INfor)
{
	if (INfor->argc != 3)
	{
		_ErrPutos("Incorrect number of arguements\n");
		return (1);
	}
	if (_EnviroSetter(INfor, INfor->argv[1], INfor->argv[2]))
		return (0);
	return (1);
}

/**
 * _EnvoCuroiroRemo - for Removing environment variable as ease
 *
 * @INfor: Structure arguments
 *
 * -Return: sucess only 0
 */

int _EnvoCuroiroRemo(info_t *INfor)
{
	int io;

	if (INfor->argc == 1)
	{
		_ErrPutos("Too few arguements.\n");
		return (1);
	}
	for (io = 1; io <= INfor->argc; io++)
		_EnviroRemo(INfor, INfor->argv[io]);

	return (0);
}

/**
 * EnvoListFrPop - for populating envpn listed
 *
 * @INfor: Structure arguments
 *
 * -Return: success only 0
 */

int EnvoListFrPop(info_t *INfor)
{
	list_t *node = NULL;
	size_t io;

	for (io = 0; environ[io]; io++)
		NodeAddetion_end(&node, environ[io], 0);
	INfor->env = node;
	return (0);
}

