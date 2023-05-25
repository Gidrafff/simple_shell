#include "shell.h"

/**
 * list_len - calculates the length of a linked list
 * @b: Pointer to the first node
 *
 * Return: The size of the list
 */
size_t list_len(const list_t *b)
{
	size_t a = 0;

	while (b)
	{
		b = b->next;
		a++;
	}
	return (a);
}

/**
 * list_to_strings - returns an array of the strings of list->str
 * @h: Pointer to the first node
 *
 * Return: Array of the strings
 */
char **list_to_strings(list_t *h)
{
	list_t *node = h;
	size_t a = list_len(h), e;
	char **strs;
	char *str;

	if (!h || !a)
		return (NULL);
	strs = malloc(sizeof(char *) * (a + 1));
	if (!strs)
		return (NULL);
	for (a = 0; node; node = node->next, a++)
	{
		str = malloc(_strlen(node->str) + 1);
		if (!str)
		{
			for (e = 0; e < a; e++)
				free(strs[e]);
			free(strs);
			return (NULL);
		}

		str = _strcpy(str, node->str);
		strs[a] = str;
	}
	strs[a] = NULL;
	return (strs);
}


/**
 * print_list - prints all elements of a list_t linked list
 * @b: pointer to first node
 *
 * Return: size of the list
 */
size_t print_list(const list_t *b)
{
	size_t a = 0;

	while (b)
	{
		_puts(convert_number(b->num, 10, 0));
		_putchar(':');
		_putchar(' ');
		_puts(b->str ? b->str : "(nil)");
		_puts("\n");
		b = b->next;
		a++;
	}
	return (a);
}

/**
 * node_starts_with - returns node whose string starts with a given prefix
 * @node: pointer to the head of the list
 * @prefix: string to match as prefix
 * @b: the next character after the prefix to match
 *
 * Return: match node or null if not found
 */
list_t *node_starts_with(list_t *node, char *prefix, char b)
{
	char *p = NULL;

	while (node)
	{
		p = starts_with(node->str, prefix);
		if (p && ((b == -1) || (*p == b)))
			return (node);
		node = node->next;
	}
	return (NULL);
}

/**
 * get_node_index - gets the index of a node
 * @h: pointer to list head
 * @node: pointer to the node
 *
 * Return: index of node, otherwise -1
 */
ssize_t get_node_index(list_t *h, list_t *node)
{
	size_t a = 0;

	while (h)
	{
		if (h == node)
			return (a);
		h = h->next;
		a++;
	}
	return (-1);
}
