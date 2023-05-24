#include "shell.h"

/**
 * bfree - frees a pointer and set the address to NULL
 * @p: address of the pointer to be freed
 *
 * Return: 1 if successfully freed, otherwise 0.
 */
int bfree(void **p)
{
	if (p && *p)
	{
		free(*p);
		p = NULL;
		return (1);
	}
	return (0);
}
