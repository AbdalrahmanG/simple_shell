#include "shell.h"

/**
 * clear_INfor - for initializing struct
 *
 * @INfor: the struct adds
 */

void clear_INfor(info_t *INfor)
{
	INfor->arg = NULL;
	INfor->argv = NULL;
	INfor->path = NULL;
	INfor->argc = 0;
}

/**
 * set_INfor - for initializing struct
 *
 * @INfor: the used struct adds
 * @av: vector argument
 */

void set_INfor(info_t *INfor, char **av)
{
	int io = 0;

	INfor->fname = av[0];
	if (INfor->arg)
	{
		INfor->argv = strng_in2(INfor->arg, " \t");
		if (!INfor->argv)
		{

			INfor->argv = malloc(sizeof(char *) * 2);
			if (INfor->argv)
			{
				INfor->argv[0] = _strDouble(INfor->arg);
				INfor->argv[1] = NULL;
			}
		}
		for (io = 0; INfor->argv && INfor->argv[io]; io++)
			;
		INfor->argc = io;

		AliasReplAlias(INfor);
		VariaPlace(INfor);
	}
}

/**
 * free_INfor - for freeing the used struct field
 *
 * @INfor: the used struct adds
 * @all: for freeing all field
 */

void free_INfor(info_t *INfor, int all)
{
	DobyFree(INfor->argv);
	INfor->argv = NULL;
	INfor->path = NULL;
	if (all)
	{
		if (!INfor->cmd_buf)
			free(INfor->arg);
		if (INfor->env)
			free_list(&(INfor->env));
		if (INfor->history)
			free_list(&(INfor->history));
		if (INfor->alias)
			free_list(&(INfor->alias));
		DobyFree(INfor->environ);
			INfor->environ = NULL;
		FreeingPoin((void **)INfor->cmd_buf);
		if (INfor->readfile_Def > 2)
			close(INfor->readfile_Def);
		_PutPcharc(BUFF_FRFLUSH);
	}
}

