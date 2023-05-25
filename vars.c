#include "shell.h"

/**
 * is_chain - test if current character in the buffer is a chain delim
 * @info: the parameter structure
 * @buf: the buffer character
 * @b: address of the  current position of the buffer
 *
 * Return: 1 if chain delim, otherwise 0
 */
int is_chain(info_t *info, char *buf, size_t *b)
{
	size_t h = *b;

	if (buf[h] == '|' && buf[h + 1] == '|')
	{
		buf[h] = 0;
		h++;
		info->cmd_buf_type = CMD_OR;
	}
	else if (buf[h] == '&' && buf[h + 1] == '&')
	{
		buf[h] = 0;
		h++;
		info->cmd_buf_type = CMD_AND;
	}
	else if (buf[h] == ';')
	{
		buf[h] = 0;
		info->cmd_buf_type = CMD_CHAIN;
	}
	else
		return (0);
	*b = h;
	return (1);
}

/**
 * check_chain - checks if to continue chaining based on last status
 * @info: the parameter structure
 * @buf: the character of the  buffer
 * @p: address of the  current position in the buffer
 * @a: The starting position in buffer
 * @l: length of the buffer
 *
 * Return: Void
 */
void check_chain(info_t *info, char *buf, size_t *p, size_t a, size_t l)
{
	size_t h = *p;

	if (info->cmd_buf_type == CMD_AND)
	{
		if (info->status)
		{
			buf[a] = 0;
			h = l;
		}
	}
	if (info->cmd_buf_type == CMD_OR)
	{
		if (!info->status)
		{
			buf[a] = 0;
			h = l;
		}
	}

	*p = h;
}

/**
 * replace_alias - replaces an aliases in a tokenized string
 * @info: the parameter structure
 *
 * Return: 1 if replaced, otherwise 0
 */
int replace_alias(info_t *info)
{
	int a;
	list_t *node;
	char *p;

	for (a = 0; a < 10; a++)
	{
		node = node_starts_with(info->alias, info->argv[0], '=');
		if (!node)
			return (0);
		free(info->argv[0]);
		p = _strchr(node->str, '=');
		if (!p)
			return (0);
		p = _strdup(p + 1);
		if (!p)
			return (0);
		info->argv[0] = p;
	}
	return (1);
}

/**
 * replace_vars - replaces vars in a tokenized string
 * @info: the parameter structure
 *
 * Return: 1 if replaced, otherwise 0
 */
int replace_vars(info_t *info)
{
	int a = 0;
	list_t *node;

	for (a = 0; info->argv[a]; a++)
	{
		if (info->argv[a][0] != '$' || !info->argv[a][1])
			continue;

		if (!_strcmp(info->argv[a], "$?"))
		{
			replace_string(&(info->argv[a]),
					_strdup(convert_number(info->status, 10, 0)));
			continue;
		}
		if (!_strcmp(info->argv[a], "$$"))
		{
			replace_string(&(info->argv[a]),
					_strdup(convert_number(getpid(), 10, 0)));
			continue;
		}
		node = node_starts_with(info->env, &info->argv[a][1], '=');
		if (node)
		{
			replace_string(&(info->argv[a]),
					_strdup(_strchr(node->str, '=') + 1));
			continue;
		}
		replace_string(&info->argv[a], _strdup(""));

		}
		return (0);
}

/**
 * replace_string - replaces string
 * @prev: Address of the prev stringto be replaced
 * @new: The new string
 *
 * Return: 1 if replaced, otherwise 0
 */
int replace_string(char **prev, char *new)
{
	free(*prev);
	*prev = new;
	return (1);
}
