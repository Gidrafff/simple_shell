#include "shell.h"

/**
 * _memset - fills memory with a constant byte
 * @t: the pointer to the memory area
 * @c: the byte to fill *t with
 * @m: the amount of bytes to be filled
 * Return: (t) a pointer to the memory t
 */
char *_memset(char *t, char c, unsigned int m)
{
	unsigned int a;

	for (a = 0; a < m; a++)
		t[a] = c;
	return (t);
}

/**
 * ffree - frees a string of strings
 * @ss: string of strings
 */
void ffree(char **ss)
{
	char **i = ss;

	if (!ss)
		return;
	while (*ss)
		free(*ss++);
	free(i);
}

/**
 * _realloc - reallocates a block of memory
 * @ptr: pointer to previous malloc'ated block
 * @prev_size: byte size of previous block mallocated
 * @new_size: byte size of new block mallocated
 *
 * Return: pointer to da ol'block nameen
 */
void *_realloc(void *ptr, unsigned int prev_size, unsigned int new_size)
{
	char *p;

	if (!ptr)
		return (malloc(new_size));
	if (!new_size)
		return (free(ptr), NULL);
	if (new_size == prev_size)
		return (ptr);

	p = malloc(new_size);
	if (!p)
		return (NULL);

	prev_size = prev_size < new_size ? prev_size : new_size;
	while (prev_size--)
		p[prev_size] = ((char *)ptr)[prev_size];
	free(ptr);
	return (p);
}
