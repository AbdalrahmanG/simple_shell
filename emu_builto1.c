#include "shell.h"

/**
 * _HistoryNow - for displaying histo list
 *
 * @INfor: Structure arguments
 *
 * -Return: success only 0
 */

int _HistoryNow(info_t *INfor)
{
	List_ToBe_print(INfor->history);
	return (0);
}

/**
 * unAlia_setter - for seting string alias
 *
 * @INfor: the used parameter struct
 * @str: the string alias
 *
 * Return: success only 0 otherwise 1
 */

int unAlia_setter(info_t *INfor, char *str)
{
	char *p, coo;
	int reto;

	p = _strngCharc(str, '=');
	if (!p)
		return (1);
	coo = *p;
	*p = 0;
	reto = delete_node_at_index(&(INfor->alias),
		index_yourNode(INfor->alias, BeginsOf_node(INfor->alias, str, -1)));
	*p = coo;
	return (reto);
}

/**
 * Alia_setter - for setting string alias
 *
 * @INfor: the usedd struct parameter
 * @str: the slias string used
 *
 * Return: success 0, otherwise 1
 */

int Alia_setter(info_t *INfor, char *str)
{
	char *p;

	p = _strngCharc(str, '=');
	if (!p)
		return (1);
	if (!*++p)
		return (unAlia_setter(INfor, str));

	unAlia_setter(INfor, str);
	return (NodeAddetion_end(&(INfor->alias), str, 0) == NULL);
}

/**
 * Alia_printing - for printing string alias
 *
 * @node: the used alias node
 *
 * Return: success 0, otherwise 1
 */

int Alia_printing(list_t *node)
{
	char *p = NULL, *a = NULL;

	if (node)
	{
		p = _strngCharc(node->str, '=');
		for (a = node->str; a <= p; a++)
			_PutPcharc(*a);
		_PutPcharc('\'');
		_PutPs(p + 1);
		_PutPs("'\n");
		return (0);
	}
	return (1);
}

/**
 * _myalias - for mimicing builtin alias
 *
 * @INfor: Structure arguments
 *
 * -Return: success only 0
 */

int _myalias(info_t *INfor)
{
	int io = 0;
	char *p = NULL;
	list_t *node = NULL;

	if (INfor->argc == 1)
	{
		node = INfor->alias;
		while (node)
		{
			Alia_printing(node);
			node = node->next;
		}
		return (0);
	}
	for (io = 1; INfor->argv[io]; io++)
	{
		p = _strngCharc(INfor->argv[io], '=');
		if (p)
			Alia_setter(INfor, INfor->argv[io]);
		else
			Alia_printing(BeginsOf_node(INfor->alias, INfor->argv[io], '='));
	}

	return (0);
}

