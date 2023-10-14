#include "shell.h"

/**
 * List_lnth - for determining length of list
 *
 * @h: first nodepointer head
 *
 * Return: list space
 */

size_t List_lnth(const list_t *h)
{
	size_t io = 0;

	while (h)
	{
		h = h->next;
		io++;
	}
	return (io);
}

/**
 * Conv_listTo_strn - for returning string array
 *
 * @head: first node pointer head
 *
 * Return: string arr
 */

char **Conv_listTo_strn(list_t *head)
{
	list_t *node = head;
	size_t io = List_lnth(head), jo;
	char **strs;
	char *str;

	if (!head || !io)
		return (NULL);
	strs = malloc(sizeof(char *) * (io + 1));
	if (!strs)
		return (NULL);
	for (io = 0; node; node = node->next, io++)
	{
		str = malloc(_StrngLnth(node->str) + 1);
		if (!str)
		{
			for (jo = 0; jo < io; jo++)
				free(strs[jo]);
			free(strs);
			return (NULL);
		}

		str = _StrnCpy(str, node->str);
		strs[io] = str;
	}
	strs[io] = NULL;
	return (strs);
}


/**
 * List_ToBe_print - for printing every elements of lists
 *
 * @h: first node pointer head
 *
 * Return: list spce
 */

size_t List_ToBe_print(const list_t *h)
{
	size_t io = 0;

	while (h)
	{
		_PutPs(Con_verNum(h->num, 10, 0));
		_PutPcharc(':');
		_PutPcharc(' ');
		_PutPs(h->str ? h->str : "(nil)");
		_PutPs("\n");
		h = h->next;
		io++;
	}
	return (io);
}

/**
 * BeginsOf_node - for returning node
 *
 * @node: list head pointer head
 * @prefix: matched string
 * @c: the following charac
 *
 * Return: the node or not
 */

list_t *BeginsOf_node(list_t *node, char *prefix, char c)
{
	char *p = NULL;

	while (node)
	{
		p = Begin_By(node->str, prefix);
		if (p && ((c == -1) || (*p == c)))
			return (node);
		node = node->next;
	}
	return (NULL);
}

/**
 * index_yourNode - for geting the node index
 *
 * @head: first node pointer head
 * @node: list head pointer head
 *
 * Return: the node or, fail -1
 */

ssize_t index_yourNode(list_t *head, list_t *node)
{
	size_t io = 0;

	while (head)
	{
		if (head == node)
			return (io);
		head = head->next;
		io++;
	}
	return (-1);
}

