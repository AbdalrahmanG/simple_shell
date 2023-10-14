#include "shell.h"

/**
 * **EnviroGetter - for returning string array comes from environment
 *
 * @INfor: Structure arguments
 *
 * -Return: success only 0
 */

char **EnviroGetter(info_t *INfor)
{
	if (!INfor->environ || INfor->env_changed)
	{
		INfor->environ = Conv_listTo_strn(INfor->env);
		INfor->env_changed = 0;
	}

	return (INfor->environ);
}

/**
 * _EnviroRemo - for Removing environment variable at ease
 *
 * @INfor: Structure arguments
 * @var: the string environment vars prop
 *
 * -Return: when delete 1, otherwise 0
 */

int _EnviroRemo(info_t *INfor, char *var)
{
	list_t *node = INfor->env;
	size_t io = 0;
	char *p;

	if (!node || !var)
		return (0);

	while (node)
	{
		p = Begin_By(node->str, var);
		if (p && *p == '=')
		{
			INfor->env_changed = delete_node_at_index(&(INfor->env), io);
			io = 0;
			node = INfor->env;
			continue;
		}
		node = node->next;
		io++;
	}
	return (INfor->env_changed);
}

/**
 * _EnviroSetter - for Initializing new environment vars as usall
 *
 * @INfor: Structure arguments
 * @var: the string environment vars prop
 * @value: the string environment vars values
 *
 * -Return: success only 0
 */

int _EnviroSetter(info_t *INfor, char *var, char *value)
{
	char *buf = NULL;
	list_t *node;
	char *p;

	if (!var || !value)
		return (0);

	buf = malloc(_StrngLnth(var) + _StrngLnth(value) + 2);
	if (!buf)
		return (1);
	_StrnCpy(buf, var);
	_StrngCat(buf, "=");
	_StrngCat(buf, value);
	node = INfor->env;
	while (node)
	{
		p = Begin_By(node->str, var);
		if (p && *p == '=')
		{
			free(node->str);
			node->str = buf;
			INfor->env_changed = 1;
			return (0);
		}
		node = node->next;
	}
	NodeAddetion_end(&(INfor->env), buf, 0);
	free(buf);
	INfor->env_changed = 1;
	return (0);
}

