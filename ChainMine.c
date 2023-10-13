#include "shell.h"

/**
 * Chk_Chain - for testing current char in buff or delimeter
 *
 * @INfor: the used parameter struct
 * @buf: the current char buff
 * @p: current buff pose
 *
 * Return: when chain delimeter 1,otherwise 0
 */

int Chk_Chain(info_t *INfor, char *buf, size_t *p)
{
	size_t jo = *p;

	if (buf[jo] == '|' && buf[jo + 1] == '|')
	{
		buf[jo] = 0;
		jo++;
		INfor->TYPO_BUFF_CMD = CMD_OR;
	}
	else if (buf[jo] == '&' && buf[jo + 1] == '&')
	{
		buf[jo] = 0;
		jo++;
		INfor->TYPO_BUFF_CMD = CMD_AND;
	}
	else if (buf[jo] == ';')
	{
		buf[jo] = 0;
		INfor->TYPO_BUFF_CMD = CMD_CHAIN;
	}
	else
		return (0);
	*p = jo;
	return (1);
}

/**
 * ChkChain_again - for checking chaining based on last status (if you know)
 *
 * @INfor: the used parameter struct
 * @buf: char buf
 * @p: current buff pose
 * @i: the started pose in buf
 * @len: buf's length
 *
 * Return: boid
 */

void ChkChain_again(info_t *INfor, char *buf, size_t *p, size_t i, size_t len)
{
	size_t jo = *p;

	if (INfor->TYPO_BUFF_CMD == CMD_AND)
	{
		if (INfor->status)
		{
			buf[i] = 0;
			jo = len;
		}
	}
	if (INfor->TYPO_BUFF_CMD == CMD_OR)
	{
		if (!INfor->status)
		{
			buf[i] = 0;
			jo = len;
		}
	}

	*p = jo;
}

/**
 * AliasReplAlias - for replacing aliases in string tokeni
 *
 * @INfor: the used parameter struct
 *
 * Return: wen replace 1,otherwise 0
 */

int AliasReplAlias(info_t *INfor)
{
	int io;
	list_t *node;
	char *p;

	for (io = 0; io < 10; io++)
	{
		node = BeginsOf_node(INfor->alias, INfor->argv[0], '=');
		if (!node)
			return (0);
		free(INfor->argv[0]);
		p = _strngCharc(node->str, '=');
		if (!p)
			return (0);
		p = _strDouble(p + 1);
		if (!p)
			return (0);
		INfor->argv[0] = p;
	}
	return (1);
}

/**
 * VariaPlace - for replacing variables in string tokeni
 *
 * @INfor: the used parameter struct
 *
 * Return: when replac 1,otherwise 0
 */

int VariaPlace(info_t *INfor)
{
	int io = 0;
	list_t *node;

	for (io = 0; INfor->argv[io]; io++)
	{
		if (INfor->argv[io][0] != '$' || !INfor->argv[io][1])
			continue;

		if (!_StrngCmpr(INfor->argv[io], "$?"))
		{
			StrngRep(&(INfor->argv[io]),
					 _strDouble(Con_verNum(INfor->status, 10, 0)));
			continue;
		}
		if (!_StrngCmpr(INfor->argv[io], "$$"))
		{
			StrngRep(&(INfor->argv[io]),
					 _strDouble(Con_verNum(getpid(), 10, 0)));
			continue;
		}
		node = BeginsOf_node(INfor->env, &INfor->argv[io][1], '=');
		if (node)
		{
			StrngRep(&(INfor->argv[io]),
					 _strDouble(_strngCharc(node->str, '=') + 1));
			continue;
		}
		StrngRep(&INfor->argv[io], _strDouble(""));
	}
	return (0);
}

/**
 * StrngRep - for replacing the given string
 *
 * @old: old string add
 * @new: new string add
 *
 * Return: when replac 1,otherwise 0
 */

int StrngRep(char **old, char *new)
{
	free(*old);
	*old = new;
	return (1);
}

