#include "shell.h"

/**
 * NodeAddetion - for adding node to start list
 *
 * @head: head node pointer
 * @str: node str-field
 * @num: node index used
 *
 * Return: list's space
 */

list_t *NodeAddetion(list_t **head, const char *str, int num)
{
	list_t *new_head;

	if (!head)
		return (NULL);
	new_head = malloc(sizeof(list_t));
	if (!new_head)
		return (NULL);
	_memset((void *)new_head, 0, sizeof(list_t));
	new_head->num = num;
	if (str)
	{
		new_head->str = _strDouble(str);
		if (!new_head->str)
		{
			free(new_head);
			return (NULL);
		}
	}
	new_head->next = *head;
	*head = new_head;
	return (new_head);
}

/**
 * NodeAddetion_end - for adding node to list's end
 *
 * @head: head node pointer
 * @str: node str-field
 * @num: node index used
 *
 * Return: list's space
 */

list_t *NodeAddetion_end(list_t **head, const char *str, int num)
{
	list_t *new_node, *node;

	if (!head)
		return (NULL);

	node = *head;
	new_node = malloc(sizeof(list_t));
	if (!new_node)
		return (NULL);
	_memset((void *)new_node, 0, sizeof(list_t));
	new_node->num = num;
	if (str)
	{
		new_node->str = _strDouble(str);
		if (!new_node->str)
		{
			free(new_node);
			return (NULL);
		}
	}
	if (node)
	{
		while (node->next)
			node = node->next;
		node->next = new_node;
	}
	else
		*head = new_node;
	return (new_node);
}

/**
 * List_ToBe_print_str - for printing strng element of linked list
 *
 * @h: first nodepointer
 *
 * Return: size of list
 */

size_t List_ToBe_print_str(const list_t *h)
{
	size_t io = 0;

	while (h)
	{
		_PutPs(h->str ? h->str : "(nil)");
		_PutPs("\n");
		h = h->next;
		io++;
	}
	return (io);
}

/**
 * delete_node_at_index - for deleting node of index
 *
 * @head: head node pointer
 * @index: index of node for deleting
 *
 * Return: when sucess 1,fail 0
 */

int delete_node_at_index(list_t **head, unsigned int index)
{
	list_t *node, *prev_node;
	unsigned int io = 0;

	if (!head || !*head)
		return (0);

	if (!index)
	{
		node = *head;
		*head = (*head)->next;
		free(node->str);
		free(node);
		return (1);
	}
	node = *head;
	while (node)
	{
		if (io == index)
		{
			prev_node->next = node->next;
			free(node->str);
			free(node);
			return (1);
		}
		io++;
		prev_node = node;
		node = node->next;
	}
	return (0);
}

/**
 * free_list - for freeing all nodes that are in list
 *
 * @head_ptro: pointer node addrs
 *
 * Return: void (nothing)
 */

void free_list(list_t **head_ptro)
{
	list_t *node, *next_node, *head;

	if (!head_ptro || !*head_ptro)
		return;
	head = *head_ptro;
	node = head;
	while (node)
	{
		next_node = node->next;
		free(node->str);
		free(node);
		node = next_node;
	}
	*head_ptro = NULL;
}

